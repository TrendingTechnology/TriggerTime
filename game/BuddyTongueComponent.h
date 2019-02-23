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

#ifndef _BUDDYTONGUECOMPONENT_H_
#define _BUDDYTONGUECOMPONENT_H_

#include "TargetableComponent.h"
#include "AudioManager.h"
#include "WeaponComponent.h"
#include "Tweening.h"
#include "SensorListener.h"
#include <boost/enable_shared_from_this.hpp>

namespace af
{
    class BuddyTongueComponent : public boost::enable_shared_from_this<BuddyTongueComponent>,
                                 public TargetableComponent,
                                 public SensorListener
    {
    public:
        explicit BuddyTongueComponent(const b2Transform& eyeletXf);
        ~BuddyTongueComponent();

        virtual ComponentPtr sharedThis() { return shared_from_this(); }

        virtual void accept(ComponentVisitor& visitor);

        virtual void update(float dt);

        virtual void sensorEnter(const SceneObjectPtr& other);

        virtual void sensorExit(const SceneObjectPtr& other);

        inline const SceneObjectPtr& rope() const { return rope_; }

        inline const WeaponComponentPtr& weapon() const { return weapon_; }
        inline void setWeapon(const WeaponComponentPtr& value) { weapon_ = value; }

    private:
        virtual void onRegister();

        virtual void onUnregister();

        b2Transform eyeletXf_;
        SceneObjectPtr rope_;
        bool dead_;
        SceneObjectPtr last_;

        float t_;
        b2Rot idleRot_;
        int idleRotDir_;

        WeaponComponentPtr weapon_;
    };

    typedef boost::shared_ptr<BuddyTongueComponent> BuddyTongueComponentPtr;
}

#endif
