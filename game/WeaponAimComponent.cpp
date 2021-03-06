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

#include "WeaponAimComponent.h"
#include "SceneObject.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Const.h"
#include "Renderer.h"
#include "Utils.h"
#include "CameraComponent.h"
#include "SceneObjectFactory.h"
#include <boost/make_shared.hpp>

namespace af
{
    WeaponAimComponent::WeaponAimComponent(SceneObjectType objectType)
    : WeaponComponent(objectType, WeaponTypeAim),
      length_(1.0f)
    {
    }

    WeaponAimComponent::~WeaponAimComponent()
    {
    }

    void WeaponAimComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitPhasedComponent(shared_from_this());
    }

    void WeaponAimComponent::update(float dt)
    {
        if (!triggerHeld()) {
            if (rc_) {
                rc_->removeFromParent();
                rc_.reset();
            }

            return;
        }

        if (!rc_) {
            b2Vec2 p = pos() + angle2vec(angle(), flashDistance());

            rc_ = boost::make_shared<RenderDottedLineComponent>(p, angle(),
                0.2f, assetManager.getDrawable("common2/dot.png"), zOrderMarker);

            rc_->setColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
            rc_->setDotVelocity(5.0f);
            rc_->setDotDistance(0.5f);

            parent()->addComponent(rc_);
        }

        b2Transform xf = b2Mul(parent()->getTransform(),
            b2Transform(pos(), b2Rot(angle())));

        b2Vec2 p1 = b2Mul(xf, b2Vec2_zero);
        b2Vec2 p2 = b2Mul(xf, b2Vec2(length_, 0.0f));

        b2Vec2 pt = p2;
        SceneObject* obj = NULL;

        scene()->rayCast(p1, p2, boost::bind(&WeaponAimComponent::rayCastCb, this,
            _1, _2, _3, _4, boost::ref(pt), boost::ref(obj)));

        float len = (pt - p1).Length() - flashDistance();

        if (len < 0.0f) {
            len = 0.0f;
        }

        rc_->setLength(len);
    }

    void WeaponAimComponent::reload()
    {
    }

    void WeaponAimComponent::onRegister()
    {
        fakeMissile_ = sceneObjectFactory.createFakeMissile(objectType());
        scene()->addObject(fakeMissile_);
    }

    void WeaponAimComponent::onUnregister()
    {
        fakeMissile_->removeFromParent();
        fakeMissile_.reset();

        if (rc_) {
            rc_->removeFromParent();
            rc_.reset();
        }
    }

    float WeaponAimComponent::rayCastCb(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float fraction, b2Vec2& finalPoint,
        SceneObject*& obj)
    {
        if (fixture->IsSensor() || !fakeMissile_->collidesWith(fixture)) {
            return -1;
        }

        finalPoint = point;
        obj = SceneObject::fromFixture(fixture);

        return fraction;
    }
}
