/*
 * Copyright (c) 2014, Stanislav Vorobiov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "WeaponMachineGunComponent.h"
#include "SceneObject.h"
#include "Scene.h"
#include "SceneObjectFactory.h"
#include "AssetManager.h"
#include "BulletComponent.h"
#include "Utils.h"
#include "Const.h"
#include "af/Utils.h"
#include <boost/make_shared.hpp>

namespace af
{
    WeaponMachineGunComponent::WeaponMachineGunComponent(SceneObjectType objectType)
    : WeaponComponent(objectType, WeaponTypeMachineGun),
      damage_(0),
      velocity_(0),
      spreadAngle_(0),
      turnInterval_(0),
      turnDuration_(0),
      loopDelay_(0),
      t_(0),
      turnT_(0),
      flashT_(0),
      tweakPos_(false),
      tweakOffset_(b2Vec2_zero),
      bulletHeight_(0.1f)
    {
        snd_[0] = audio.createSound("machinegun_fire1.ogg");
        snd_[1] = audio.createSound("machinegun_fire2.ogg");
        snd_[2] = audio.createSound("machinegun_fire3.ogg");
        snd_[3] = audio.createSound("machinegun_fire4.ogg");
    }

    WeaponMachineGunComponent::~WeaponMachineGunComponent()
    {
    }

    void WeaponMachineGunComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhasedComponent(shared_from_this());
    }

    void WeaponMachineGunComponent::update(float dt)
    {
        t_ -= dt;
        flashT_ -= dt;

        if (flashT_ <= 0.0f) {
            flash_->setVisible(false);
            flashAc_->startAnimation(AnimationNone);
            light_->setVisible(false);
        }

        if ((t_ > 0.0f) || !triggerHeld()) {
            return;
        }

        if (!changeAmmo(1)) {
            return;
        }

        b2Transform xf;

        if (tweakPos_) {
            xf = b2Mul(parent()->getTransform(),
                b2Transform(tweakOffset_, b2Rot(angle())));
        } else {
            xf = b2Mul(parent()->getTransform(),
                b2Transform(pos(), b2Rot(angle())));
        }

        scene()->stats()->incShotsFired(this);

        SceneObjectPtr shot = sceneObjectFactory.createBullet(objectType(), bulletHeight_, damage_);

        float a = getRandom(-spreadAngle_ / 2.0f, spreadAngle_ / 2.0f);

        b2Transform realXf = xf;

        realXf.q = b2Mul(realXf.q, b2Rot(a));

        shot->setTransform(realXf);
        shot->setLinearVelocity(shot->getDirection(velocity_));

        if (tweakPos_) {
            shot->findComponent<BulletComponent>()->setStartPos(parent()->getWorldPoint(pos()));
        }

        setupShot(shot);

        scene()->addObject(shot);

        flash_->setPos(pos() + angle2vec(angle(), 0.32f * flash_->width() + flashDistance()));
        flash_->setAngle(angle());
        flash_->setVisible(flashQuad());
        if (flashQuad()) {
            flashAc_->startAnimation(AnimationDefault);
        } else {
            flashAc_->startAnimation(AnimationNone);
        }

        light_->setPos(flash_->pos());
        light_->setVisible(true);

        flashT_ = 0.05f;

        if (haveSound()) {
            for (int i = 0; i < 4; ++i) {
                snd_[i]->stop();
            }
            snd_[rand() % 4]->play();
        }

        updateCrosshair();

        if (turnT_ >= turnDuration_) {
            t_ = loopDelay_;
            turnT_ = 0.0f;
        } else {
            t_ = turnInterval_;
            turnT_ += turnInterval_;
        }
    }

    void WeaponMachineGunComponent::reload()
    {
        t_ = loopDelay_;
        turnT_ = 0.0f;
    }

    void WeaponMachineGunComponent::onRegister()
    {
        DrawablePtr drawable = assetManager.getDrawable("factory4/flash1.png");

        float height = 2.5f;
        float width = height * drawable->image().aspect();

        flash_ =
            boost::make_shared<RenderQuadComponent>(
                pos() + angle2vec(angle(), 0.32f * width + flashDistance()),
                angle(), width, height,
                drawable, zOrderEffects);
        flash_->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
        flash_->setVisible(false);

        parent()->addComponent(flash_);

        flashAc_ = boost::make_shared<AnimationComponent>(drawable);
        flashAc_->addAnimation(AnimationDefault, "flash");

        parent()->addComponent(flashAc_);

        light_ = boost::make_shared<PointLight>();
        light_->setVisible(false);
        light_->setColor(Color(0.4f, 0.4f, 0.0f, 1.0f));
        light_->setDiffuse(false);
        light_->setXray(true);
        light_->setDistance(6.0f);
        light_->setPos(flash_->pos());

        lightC_ = boost::make_shared<LightComponent>();

        lightC_->attachLight(light_);

        parent()->addComponent(lightC_);
    }

    void WeaponMachineGunComponent::onUnregister()
    {
        flash_->removeFromParent();
        flashAc_->removeFromParent();
        lightC_->removeFromParent();
    }
}
