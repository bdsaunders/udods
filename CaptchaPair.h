/* CaptchaPair.h
 *
 * Captcha (id,text) pairs and support for hashing them.
 * This header is shared by server simulators and clients simulators.
 * 
 * 2014Apr -bds
*/
#ifndef CAPTCHAPAIR_H
#define CAPTCHAPAIR_H
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// section shared with server simulators //
typedef int User; // 1..2^30 are User id's 
typedef int Text ; // 1..99999 are captcha Texts, 0 and 100000 are signals. 

struct CaptchaPair {
    User userID;
    Text captchaText;

    CaptchaPair(int id = 0, int captcha = 0) { reset(id, captcha); }
    void reset(int id = 0, int captcha = 0)
    {   userID = id; captchaText = captcha; }
};

// support functions for USets of CaptchaPairs

int hashCode(CaptchaPair p) { return p.userID; }

bool operator==(CaptchaPair a, CaptchaPair b)
{ return a.userID == b.userID; }

bool operator!=(CaptchaPair a, CaptchaPair b)
{ return a.userID != b.userID; }

// support function for SSets of CaptchaPairs

int compare(CaptchaPair a, CaptchaPair b) { return a.time - b.time; }

// support for debugging

ostream& operator<<(ostream& os, const CaptchaPair& p) {
	os << "[" << p.userID << "," << p.captchaText << "]"; 
	return os; 
}


#endif // CAPTCHAPAIR_H
