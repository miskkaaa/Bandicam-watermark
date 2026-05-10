#include <Geode/Geode.hpp>

using namespace geode::prelude;

/*
        auto enabled = Mod::get()->getSettingValue<bool>("enabled");
        if (enabled) {
            auto transparency = Mod::get()->getSettingValue<float_t>("transparency");
            auto winSize = CCDirector::sharedDirector()->getWinSize();

            m_fields->m_bSpr = CCSprite::create("bandicam.png"_spr);

            if (m_fields->m_bSpr) {
                m_fields->m_bSpr->setAnchorPoint({0.5f,1.0f});
                m_fields->m_bSpr->setPosition({winSize.width/2.0f,winSize.height});
                m_fields->m_bSpr->setZOrder(42069);
                m_fields->m_bSpr->  setOpacity(transparency);

                this->addChild(m_fields->m_bSpr);
            }
        }
*/

#define SHIT "bandicam_overlay"

CCSprite* getw() {
    auto overlay = OverlayManager::get();
    return dynamic_cast<CCSprite*>(overlay->getChildByID(SHIT));
}

void bscreate() {
    auto shit = Mod::get();
    auto overlay = OverlayManager::get();

    if (!shit->getSettingValue<bool>("enabled")) return;

    if (getw()) return;

    auto ws = CCDirector::sharedDirector()->getWinSize();
    auto transp = shit->getSettingValue<float_t>("transparency");

    auto spr = CCSprite::create("bandicam.png"_spr);
    if (!spr) return;

    spr->setID(SHIT);
    spr->setAnchorPoint({0.5f, 1.0f});
    spr->setPosition({ws.width / 2.0f, ws.height});
    spr->setZOrder(42069);
    spr->setOpacity(transp);

    overlay->addChild(spr);
}

$on_mod(Loaded) {
    bscreate();

    listenForSettingChanges<float_t>("transparency", [](float_t val) {
        if (auto spr = getw()) {
            spr->setOpacity(val);
        }
    });

    listenForSettingChanges<bool>("enabled", [](bool val) {
        if (auto spr = getw()) {
            spr->setVisible(val);
        } else if (val) {
            bscreate();
        }
    });
}

/*

class $modify(PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSave) {
        if (!PlayLayer::init(level, useReplay, dontSave)) return false;
        bscreate();
        return true;
    }
};
class $modify(LevelEditorLayer) {
  bool init(GJGameLevel* level, bool p1) {
      if (!LevelEditorLayer::init(level, p1)) return false;
      bscreate();
      return true;
  }
};
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        bscreate();
        return true;
    }
};

*/