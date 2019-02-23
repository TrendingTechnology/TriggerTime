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

#include "BossSkullComponent.h"
#include "ExplosionComponent.h"
#include "SceneObjectFactory.h"
#include "RenderHealthbarComponent.h"
#include "AssetManager.h"
#include "Scene.h"
#include "Const.h"
#include "WeaponBlasterComponent.h"

namespace af
{
    BossSkullComponent::BossSkullComponent(const Guns& guns, const Guns& flamethrowers)
    : TargetableComponent(phaseThink),
      guns_(guns),
      flamethrowers_(flamethrowers),
      t_(0.0f),
      hadTarget_(false)
    {
    }

    BossSkullComponent::~BossSkullComponent()
    {
    }

    void BossSkullComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhasedComponent(shared_from_this());
    }

    void BossSkullComponent::update(float dt)
    {
        if (parent()->life() <= 0) {
            t_ -= dt;

            if (t_ > 0.0f) {
                return;
            }

            for (Guns::const_iterator it = guns_.begin(); it != guns_.end(); ++it) {
                (*it)->setTarget(SceneObjectPtr());
            }

            RenderHealthbarComponentPtr hc = parent()->findComponent<RenderHealthbarComponent>();
            if (hc) {
                hc->removeFromParent();
            }

            if (parent()->objects().empty()) {
                SceneObjectPtr explosion = sceneObjectFactory.createExplosion1(zOrderExplosion);

                explosion->setTransform(parent()->getTransform());

                scene()->addObject(explosion);

                ParticleEffectComponentPtr pec = assetManager.getParticleEffect("fire1.p",
                    b2Vec2_zero, 0.0f, false);

                pec->setFixedAngle(true);

                pec->setZOrder(zOrderEffects);

                pec->resetEmit();

                parent()->addComponent(pec);

                parent()->body()->SetType(b2_kinematicBody);

                scene()->stats()->incEnemiesKilled();

                removeFromParent();
            } else {
                SceneObjectPtr toKill = *parent()->objects().begin();

                SceneObjectPtr explosion = sceneObjectFactory.createExplosion1(zOrderExplosion);

                explosion->setTransform(toKill->getTransform());

                scene()->addObject(explosion);

                t_ = (parent()->objects().size() <= 1) ? 1.0f : 0.4f;

                ParticleEffectComponentPtr pec = assetManager.getParticleEffect("fire1.p",
                    b2Vec2_zero, 0.0f, false);

                pec->setTransform(b2Transform(parent()->getLocalPoint(toKill->pos()), b2Rot(0.0f)));

                pec->setFixedAngle(true);

                pec->setZOrder(zOrderEffects);

                pec->resetEmit();

                parent()->addComponent(pec);

                toKill->removeFromParent();
            }

            return;
        }

        updateAutoTarget(dt);

        if (target() && !hadTarget_) {
            hadTarget_ = true;
            parent()->setInvulnerable(false);
            parent()->body()->SetType(b2_dynamicBody);
            for (Guns::const_iterator it = guns_.begin(); it != guns_.end(); ++it) {
                (*it)->parent()->body()->SetType(b2_dynamicBody);
            }
        }

        for (Guns::const_iterator it = guns_.begin(); it != guns_.end(); ++it) {
            (*it)->setTarget(target());
        }
    }

    void BossSkullComponent::setAmplified()
    {
        for (Guns::const_iterator it = flamethrowers_.begin(); it != flamethrowers_.end(); ++it) {
            (*it)->setAlwaysFire(true);
        }
        for (Guns::const_iterator it = guns_.begin(); it != guns_.end(); ++it) {
            for (BossSkullGunComponent::Weapons::const_iterator jt = (*it)->weapons().begin();
                jt != (*it)->weapons().end(); ++jt) {
                WeaponBlasterComponentPtr weapon = boost::dynamic_pointer_cast<WeaponBlasterComponent>(*jt);
                if (weapon) {
                    weapon->setLoopDelay(weapon->loopDelay() * 0.5f);
                }
            }
        }
    }

    void BossSkullComponent::onRegister()
    {
        scene()->stats()->incEnemiesSpawned();

        parent()->setInvulnerable(true);
    }

    void BossSkullComponent::onUnregister()
    {
        setTarget(SceneObjectPtr());
    }
}
