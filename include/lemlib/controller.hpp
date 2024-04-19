#pragma once
#include "api.h"

namespace controller {
    inline pros::Controller master(pros::E_CONTROLLER_MASTER);
    class Button{
        private:
        bool prevpressing = false;
        const pros::controller_digital_e_t button;

        int switchedTime = 0;
        public:
        bool pressing = false;
        bool pressed = false;
        bool released = false;
        int heldTimer = 0;
        int releasedTimer = 0;

        Button(pros::controller_digital_e_t button)
        :button(button)
        {
        }
        void update(){
            pressing = master.get_digital(button);

            if(pressing != prevpressing){
                pressed = pressing;
                released = !pressing;
                switchedTime = pros::millis();
            }
            else{
                pressed = false;
                released = false;
            }

            if(pressing){
                releasedTimer = pros::millis()-switchedTime;
            }
            else{
                heldTimer = pros::millis()-switchedTime;
            }

            prevpressing = pressing;
        }
    };
    inline Button R1(pros::E_CONTROLLER_DIGITAL_R1);
    inline Button R2(pros::E_CONTROLLER_DIGITAL_R2);
    inline Button L1(pros::E_CONTROLLER_DIGITAL_L1);
    inline Button L2(pros::E_CONTROLLER_DIGITAL_L2);
    inline Button X(pros::E_CONTROLLER_DIGITAL_X);
    inline Button A(pros::E_CONTROLLER_DIGITAL_A);
    inline Button Up(pros::E_CONTROLLER_DIGITAL_UP);
    inline Button Down(pros::E_CONTROLLER_DIGITAL_DOWN);
    inline Button Left(pros::E_CONTROLLER_DIGITAL_LEFT);
    inline Button Right(pros::E_CONTROLLER_DIGITAL_RIGHT);

    inline void update(){
        controller::R2.update();
        controller::L1.update();
        controller::L2.update();
        controller::R1.update();
        controller::Up.update();
        controller::A.update();
        controller::X.update();
        controller::Right.update();
        controller::Left.update();
        controller::Down.update();
    }
    
    float driveCurve(float input, float deadzone, float scale, float maxjoy, float minvolt, float maxvolt) {
        if(fabs(input)>deadzone){
            return (input *
        (powf(2.718, -(scale / (0.1* maxjoy))) + powf(2.718, (fabs(input) - maxjoy) / (0.1*maxjoy)) * (1 - powf(2.718, -(scale / (0.1*maxjoy))))) 
        *(1-(minvolt/maxvolt)) * (maxvolt/maxjoy) + minvolt * lemlib::sgn(input));
        }
        else{
            return 0;
        }
    }
}
