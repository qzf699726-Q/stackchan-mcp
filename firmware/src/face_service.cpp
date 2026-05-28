#include "face_service.h"
#include "globals.h"
#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

static Avatar avatar;
static FaceExpression currentExpr = FACE_IDLE;
static WhaleFace currentFace = WHALE_CALM;

void initFace() {
    avatar.init(8);
    avatar.setScale(1.0);
    avatar.setPosition(0, 0);
    Serial.println("[FACE] Avatar ready");
}

void setFaceExpression(FaceExpression expr) {
    currentExpr = expr;
    switch (expr) {
        case FACE_IDLE:
            if (serverHour >= 19 || (serverHour >= 0 && serverHour < 7)) {
                avatar.setExpression(Expression::Sleepy);
                currentFace = WHALE_SLEEPY;
            } else {
                avatar.setExpression(Expression::Neutral);
                currentFace = WHALE_CALM;
            }
            break;
        case FACE_LISTENING:
            avatar.setExpression(Expression::Doubt);
            currentFace = WHALE_THINKING;
            break;
        case FACE_PLAYING:
            avatar.setExpression(Expression::Happy);
            currentFace = WHALE_HAPPY;
            break;
        case FACE_THINKING:
            avatar.setExpression(Expression::Doubt);
            currentFace = WHALE_THINKING;
            break;
        case FACE_HAPPY:
            avatar.setExpression(Expression::Happy);
            currentFace = WHALE_HAPPY;
            break;
        default:
            avatar.setExpression(Expression::Neutral);
            currentFace = WHALE_CALM;
            break;
    }
}

void setMouthOpen(float ratio) {
    avatar.setMouthOpenRatio(ratio);
}

void setWhaleFace(WhaleFace face) {
    currentFace = face;
    switch (face) {
        case WHALE_CALM:     avatar.setExpression(Expression::Neutral); break;
        case WHALE_THINKING: avatar.setExpression(Expression::Doubt); break;
        case WHALE_HAPPY:    avatar.setExpression(Expression::Happy); break;
        case WHALE_SLEEPY:   avatar.setExpression(Expression::Sleepy); break;
        case WHALE_SHY:      avatar.setExpression(Expression::Happy); break;
        case WHALE_SMUG:     avatar.setExpression(Expression::Neutral); break;
        case WHALE_POUTY:    avatar.setExpression(Expression::Sad); break;
        default:             avatar.setExpression(Expression::Neutral); break;
    }
}

const char* getCurrentFaceName() {
    switch (currentFace) {
        case WHALE_CALM:     return "calm";
        case WHALE_THINKING: return "thinking";
        case WHALE_HAPPY:    return "happy";
        case WHALE_SLEEPY:   return "sleepy";
        case WHALE_SHY:      return "shy";
        case WHALE_SMUG:     return "smug";
        case WHALE_POUTY:    return "pouty";
        default:             return "unknown";
    }
}
