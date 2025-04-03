#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

//Not sure if I'm gonna do all the behavior stuffs here, maybe will do it in another class?
void App::Update(){
    double deltaTime = m_Time.GetDeltaTimeMs();
    if (deltaTime > 0.02){
        deltaTime = 0.02;
    }

    //CollisionManager Test
    //*A Important note here
    //CManager's UpdateProcess() *HAS* to be executed before PhysicProcess() of character
    //(Not sure if it's the same for other character, but for Mario it has to be this way)
    mario->Behavior();
    CManager->UpdateProcess(deltaTime);
    mario->PhysicProcess(deltaTime);
    MManager->DestroyMarkedObject(m_Renderer);
    //LOG_DEBUG(mario->GetAnimationObject()->GetPosition());
    //Fireball Shoot test
    FireballUpdate();

    //Mario mode testing
    if (Util::Input::IsKeyPressed(Util::Keycode::Z)){
        mario->StateUpdate(Mario::Mode::SMALL);
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::X)){
        mario->StateUpdate(Mario::Mode::BIG);
    }
    else if (Util::Input::IsKeyPressed(Util::Keycode::C)){
        mario->StateUpdate(Mario::Mode::FIRE);
    }


    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    CamPosAdjust();

    m_Renderer.Update(CameraPosition);
}