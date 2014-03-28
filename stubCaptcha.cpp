#include <iostream>
#include "CaptchaClientsSim1.h" // also includes CaptchaPair

int main() {
        int n = 10; //number of unique customer ids to use.
        int m = 100; //number of client actions to process in the simulation.
        CaptchaPair p_in, p_out;
        CaptchaClientsSim1 C(n);

        for (int i = 0; i < m; ++i) {
                p_in = C.ClientReqOrSol();
//      for (p_in = C.ClientReqOrSol(); p_in.userID != 0; p_in = C.ClientReqOrSol()) {
                std::cout << std::endl << "handling: " << p_in.userID << " " << p_in.captchaText << std::endl;

                p_out.userID = p_in.userID;

                if (p_in.captchaText == 0) { //it's a request
                        p_out.captchaText = rand()%99999 + 1;
                } else {                     // it's a proposed solution 
                        p_out.captchaText = 100000; // not right: all pass!
                }

                std::cout << "response: " << p_out.userID << " " << p_out.captchaText << std::endl;
                C.ServerResponse(p_out);
        }
}
