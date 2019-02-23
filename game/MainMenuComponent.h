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

#ifndef _MAINMENUCOMPONENT_H_
#define _MAINMENUCOMPONENT_H_

#include "UIComponent.h"
#include "Image.h"
#include "Tweening.h"

namespace af
{
    class MainMenuComponent : public UIComponent
    {
    public:
        MainMenuComponent();
        ~MainMenuComponent();

        virtual void update(float dt);

        virtual void render();

        void addItem(const std::string& image);

    private:
        void renderQuad(const Image& image, const b2Vec2& pos,
                        float width, float height);

        virtual void onPressed(int i) = 0;

        Image logo_;
        std::vector<Image> items_;

        int currentItem_;
        TweeningPtr tweening_;
        float time_;
        float selectionTimeout_;
        int finger_;
        int fingerItem_;
    };

    typedef boost::shared_ptr<MainMenuComponent> MainMenuComponentPtr;
}

#endif
