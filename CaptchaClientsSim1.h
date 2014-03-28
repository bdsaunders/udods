#ifndef CAPTCHACLIENTESSIM1_H
#define CAPTCHACLIENTESSIM1_H
#include <iostream>
#include <cstdlib>

struct CaptchaPair {
    int userID;
    int captchaText;
    CaptchaPair(int id = 0, int captcha = 0) {
        userID = id; captchaText = captcha; }
};
// support functions for USets of CaptchaPairs
int hashCode(CaptchaPair p) { return p.userID; }
bool operator==(CaptchaPair a, CaptchaPair b)
{ return a.userID == b.userID; }
bool operator!=(CaptchaPair a, CaptchaPair b)
{ return a.userID != b.userID; }

typedef int User; // any pos int is a User.  zero is NOT a User.
// support function for USets of Users
int hashCode(User id) { return id; }

#include "ChainedHashTable.h"

typedef int Text ; // 1..99999 are captcha Texts, 0 and 100000 are signals. 

class CaptchaClientsSim1 {
public:
    /* Give a simulated input to server.  
       Either request a challenge or solve one. */
    CaptchaPair ClientReqOrSol();

    // Receive server's response.
    void ServerResponse(CaptchaPair x);

    // constructor
    CaptchaClientsSim1(int nn = 10/*00000*/) {
        n = nn;
        for (int i = 1; i <= nn; ++i) unchallenged.add(i);
    }
protected:
    int n; // number of clients (potentially)

    ods::ChainedHashTable<CaptchaPair> challenges; // USet of pending challenges.
    /* Let text = captchaText in a CaptchaPair.
        text = 0 from this client simulator means it is a request for challenge.  
            From the server it means the current solution was false.
        0 < text < 100000 represents a captchaText, from the server it is a 
            challenge, from the client it is a solution attempt.  
            Note: in practice server challenge is presented in garbled form 
            to the user.
        text = 100000 from the server means a successful solution of a 
            challenge.  client never sends this text.
    */

    ods::ChainedHashTable<User> challenged; // USet with random() of ids
    ods::ChainedHashTable<User> unchallenged; // USet with random() of ids

    CaptchaPair cp; // the pending request or solution proposal

    Text randomText() { return rand()%99999 + 1; }

}; // class captchaClientsSim1
CaptchaPair CaptchaClientsSim1::ClientReqOrSol() {
    User id;
choose: // choose an intention and id for it.
    if (rand()%2 == 0) {
    // 50% of the time some client is requesting a challenge.

        if (rand()%5 > 0 and unchallenged.size() > 0) {
        // 80% of requests are new, first time requests.
            id = unchallenged.random();
            unchallenged.remove(id);
            challenged.add(id);

        } else if (challenged.size() > 0) {
        // 20% of requests are a client making a repeat request.
            id = challenged.random();

        } else goto choose; // no challenged/unchallenged id as wanted, try again.

        cp.userID = id;
        cp.captchaText = 0;

    } else {
    // 50% of the time some client is trying to solve a challenge.    
        int tenway = rand()%10;

        if (tenway == 0 and unchallenged.size() > 0) {
        // 10% of solutions are bogus (no prior request for challenge)
            cp.userID = unchallenged.random();
            cp.captchaText = randomText();

        } else if (tenway > 2 and challenged.size() > 0) {
        // 70% of solutions are correct 
            cp.userID = challenged.random();
            cp = challenges.find(cp);

        } else if (challenged.size() > 0) {
        // 20% of solutions are incorrect 
            cp.userID = challenged.random();
            cp = challenges.find(cp);
            Text t = randomText();
            while (t == cp.captchaText) t = randomText();
            cp.captchaText = t;

        } else goto choose; // no challenged/unchallenged id as wanted, try again
    }
    return cp; // note: next server response must be about this req/sol.
}

void CaptchaClientsSim1::ServerResponse(CaptchaPair x){
    if (x.userID != cp.userID) {
        if (x.captchaText == 0)
            std::cout << "Error, This response is not to the id, " << cp.userID << " that made the request." << std::endl;
        else
            std::cout << "Error, This response is not to the id, " << cp.userID << " that proposed a challenge solution." << std::endl;

        exit(-1);
    }
    // Here on down x.userID is valid (equals cp.userID).
    if (cp.captchaText == 0) {// it was a request
        if (1 > x.captchaText or 99999 < x.captchaText) { // server messed up
            std::cout << "Error, server must give a valid challenge text to a captcha request." << std::endl;
            exit(-1);
        } else { // record the challenge for future solution
            if (not challenges.add(x)) {
                challenges.remove(x);
                challenges.add(x);
            }
            unchallenged.remove(x.userID);
        }
    } else { // it was a solution attempt

        if (x.captchaText != 0 and x.captchaText != 100000) {
            std::cout << "Error, server must respond negatively, 0, or positively, 10000, to a solution attempt.  Response was " << x.captchaText <<  std::endl;
            exit(-1);
        }
        CaptchaPair check = challenges.find(cp);
        if (check.captchaText == cp.captchaText) { // solution was correct
            if (x.captchaText != 100000) {
                std::cout << "Error, server must respond positively to a correct solution.  Response was " << x.captchaText <<  std::endl;
            } else { // successful response
                challenges.remove(cp);
                challenged.remove(cp.userID);
                unchallenged.add(cp.userID);
               // ... continue with process, user now captcha-validated as human.
            }
        } else if (x.userID != challenged.find(x.userID)) { // solution was incorrect 
            if (x.captchaText != 0) {
                std::cout << "Error, server must respond negatively to an incorrect solution.  Response was " << x.captchaText <<  std::endl;
            } else { // successful response
                challenges.remove(cp);
                challenged.remove(cp.userID);
                unchallenged.add(cp.userID);
                // most users would follow with another request...
            }
        } else { // solution was bogus
            if (x.captchaText != 0) {
                std::cout << "Error, server must respond negatively to a bogus solution.  Response was " << x.captchaText <<  std::endl;
            } else {
                ; // nothing need be done, id is still unchallenged.
            }
        }
    }
}

#endif // CAPTCHACLIENTESSIM1_H
