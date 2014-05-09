/* CaptchaClientsSim2.h
 *
 * Simulator of captcha clients designed to check a little that snoozer's 
 * requests are ignored.
 * 
 * 2014Apr -bds
*/
#ifndef CAPTCHACLIENTESSIM2_H
#define CAPTCHACLIENTESSIM2_H
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "CaptchaPair.h"
#include "ChainedHashTable.h"

// section simulating the world of clients for a server //
enum ClientAction {firstReq, subsequentReq, falseSol, trueSol, bogusSol, fossilSol};

class CaptchaClientsSim2 {
public:
    /* Give a simulated input to server.  
       Either request a challenge or solve one. */
    CaptchaPair ClientReqOrSol();

    // Receive server's response.
    void ServerResponse(CaptchaPair x);

    // constructor
    CaptchaClientsSim2(int nn = 1000000) {
        n = nn; k = 0;
    }
protected:
    int n; // maximal number of challenges outstanding.  Must be one million finally, but may be as small as 10 for testing.

    int k; // current interaction number.
    ods::ChainedHashTable<CaptchaPair> challenges; // USet of pending challenges.
    /* Let text = captchaText in a CaptchaPair.
        text = 0 from this client simulator means it is a request for challenge.  
            From the server it means the current solution was from a client that didn't have a challenge outstanding.
        0 < text < 100000 represents a captchaText, from the server it is a 
            challenge, from the client it is a solution attempt.  
            Note: in practice, server challenge would be presented in 
            garbled form to the user.
        text = 100000 from the server means a successful solution of a 
            challenge.  clients never send this text.
    */

    CaptchaPair cp; // the pending request or solution proposal
    CaptchaPair cp2, cp3; // a couple of special cases
    ClientAction action; // the type of the pending request

    Text randomText() { return rand()%99999 + 1; }
    User randomUser() { 
        int x = (rand()*(1<<16) + rand());
        if (x < 0) x = -x;
        return x%999999999 + 1; 
    }

}; // class captchaClientsSim2

CaptchaPair CaptchaClientsSim2::ClientReqOrSol() {

    if (k < n+15) {// initial buildup and checks
	if (k == n/2) {// explicit subsequentReq 
		cp = cp2; 
		action = subsequentReq;
	} else if (k == n-4) {// explicit subsequentReq
		cp = cp2;
		action = subsequentReq;
	} else if (k == n-3) {// explicit subsequentReq
		cp = cp3;
		action = subsequentReq;
	} else if (k == n+13) {// fossil subsequentReq
		cp = cp3;
		action = fossilSol;
	} else if (k == n+14) {// fossil subsequentReq 
		cp = cp2;
		action = fossilSol;
	} else { // new req
		do { cp.userID = randomUser(); } 
                    while (challenges.find(cp) != CaptchaPair());
		cp.captchaText = 0;
		action = firstReq;
	}
    } else {// standard pattern
	int dodeca = rand()%20;
	action = dodeca < 8 ? firstReq : 
		 dodeca < 10 ? subsequentReq :
		 dodeca < 16 ? trueSol :
		 dodeca < 19 ? falseSol : bogusSol;
	
    }
    switch (action) {
    	case firstReq: //first time request, 40
            do { cp.userID = randomUser(); } 
            while (challenges.find(cp) != CaptchaPair());
                cp.captchaText = 0;
            break;
        case subsequentReq: //repeat request, 10
            cp = challenges.random();
            cp.captchaText = 0;
            break;
        case trueSol: // 30
            cp = challenges.random();
            break;
        case falseSol: // 15
            cp = challenges.random();
            Text t;
            do {t = randomText(); } while (t == cp.captchaText);
            cp.captchaText = t;
            break;
        case bogusSol: // 
            do { cp.userID = randomUser(); } 
            while (challenges.find(cp) != CaptchaPair());	
            cp.captchaText = randomText();
            break;
        case fossilSol: // can't get here
            cp.captchaText = randomText();
            break;
    }
	cout << action << " ";
    if (k == 2) {cp2 = cp; cp2.captchaText = randomText();}
    if (k == 3) {cp3 = cp; cp3.captchaText = randomText();}
    return cp;
}

void CaptchaClientsSim2::ServerResponse(CaptchaPair x){
    if (x.userID != cp.userID) {
        if (cp.captchaText == 0)
            cout << "Error, This response is not to the id, " << cp.userID << " that made the request." << endl;
        else
            cout << "Error, This response is not to the id, " << cp.userID << " that proposed a challenge solution." << endl;

        exit(-1);
    }
    // Here on down x.userID is valid (equals cp.userID).
 switch (action) {
 	case firstReq: //first time request
	case subsequentReq: //subsequent request
		if (1 > x.captchaText or 99999 < x.captchaText) { // server messed up
			cout << "Error, server must give a valid challenge text to a captcha request." << x << endl;
			exit(-1);
        	} else { // record the challenge for future solution
			if (not challenges.add(x)) 
				challenges.remove(x);
			challenges.add(x);
		}
		break;
	case trueSol:
		if (x.captchaText == 100000 // true to me and to server
                         or 
                    k >= n and x.captchaText == 0) {// true to me, fossil to server 
		// Remark: not a thorough check
			challenges.remove(cp);
			/* busy wait to simulate server processing validated user
			int work = 999999;
			for (int i = 2000; i > 0; --i) work = work % i;
			*/
		} else { // server mistake
			cout << "Error, server must respond 100000 to a correct solution, 0 to a snoozer's solution.  Response was " << x.captchaText <<  endl;
		}
		break;
	case falseSol:
		if (0 < x.captchaText and x.captchaText < 100000
			or  k >= n and x.captchaText == 0) {
			challenges.remove(cp);
			challenges.add(x);
		} else { // server mistake
			cout << "Error, server must respond with new challenge text to an incorrect solution or 0 to a snoozer's solution.  Response was " << x.captchaText <<  endl;
			exit(-1);
		}
		break;
	case bogusSol:
		if (x.captchaText != 0) {
			cout << "Error, server must respond with 0 to a bogus solution attempt (where there was no challenge).  Response was " << x.captchaText <<  endl;
			exit(-1);
		}
		break;
	case fossilSol:
		if (x.captchaText != 0) {
			cout << "Error, server must respond with 0 to a snoozer's solution attempt (where there were over " << n << " intervening challenges).  Response was " << x.captchaText <<  endl;
			exit(-1);
		}
		break;
	}
	++k; 
	return;
}

#endif // CAPTCHACLIENTESSIM2_H
