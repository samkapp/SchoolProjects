/**
* Project One 
*
* Projectile Game: Player chooses a distance and then has to 'launch' a projectile 
* by giving a velocity and angle to launch it. If the projectiles distance comes 
* within 0.1% of the originally given distance the player wins the game. 
* 
*@author Sam Kapp 
*@date 1/24/2023
*/
#include <iostream> 
#include <cmath> 

using namespace std;

double getDistance(double velocity, double angle); 
double getRads(double degrees);

int main()
{
    while (true) {
        int tries = 5; 

        double targetDistance = 0; 
        double projectileDistance = 0; 

        double playerVelocity; 
        double playerAngle; 

        cout << "Welcome to the projectile game!" << endl;
        cout << "Start by entering a distance to a target." << endl;
        cout << "And then 'shoot' a projectile by giving a velocity and angle." << endl; 
        cout << "Win by having the projectile land within 0.1 percent of the target distance" << endl;

        while (true) {
            cout << "Enter a starting distance: "; 
            cin >> targetDistance;
            cout << endl;

            // Makes sure a valid number was inputted
            if (cin.fail() || targetDistance < 0) {
                cout << "\nInvalid Input. Distance must be a positive number." << endl;

                cin.clear(); 
                cin.ignore(256, '\n');

                continue;
            }
            break;
        }
    

        double distanceThreshold = targetDistance * .001; // 0.1% Distance that projectile needs to land in

        for (int i = tries; i > 0; i--) {
            cout << i << " attemps remaining " << endl;

            cout << "Enter a positive velocity and angle: ";
            cin >> playerVelocity;
            cin >> playerAngle;

            // Makes sure a valid number was inputted
            if (cin.fail() || playerVelocity < 0 || playerAngle < 0) {
                cout << "\nInvlaid Input. Velocity and angle must be positive numbers." << endl; 

                cin.clear(); 
                cin.ignore(256, '\n');

                i++; 
                continue;
            }

            projectileDistance = getDistance(playerVelocity, playerAngle);

            // Checks if distance from projectile to given distance is close enough
            if (abs(projectileDistance - targetDistance) <= distanceThreshold){ 
                cout << "You launched the projectile " << projectileDistance << " meters!" << endl;
                cout << "\nCongratulations! You Win!" << endl << endl;
                break;
            } else {
                cout << "You launched the projectile " << projectileDistance << " meters!" << endl;
                cout << "Missed by " << targetDistance - projectileDistance << " meters." << endl << endl;

                if (i == 1) 
                    cout << "Game Over!" << endl;
            }
        }

        // checks to see if user wants to play again or leave
        int continueGame = 0;
        cout << "Enter '1' to continue or anything else to exit." << endl;
        cin >> continueGame;

        if (continueGame != 1) break;
    }
    
    cout << "See you next time!" << endl;   
}

/**
* Calculates and returns the distance a projectile travels  
* 
* distance = (velocity^2 * sin(2*angle)) / 32.2
*
* Preconditions: 
*   - velocity must be positive 
*   - angle must be positive 
* 
* Postconditions: 
*   - the distance the projectile travels has been returned
*/
double getDistance(double velocity, double angle) {
    if (velocity < 0 || angle < 0)
        return -1.0;
    
    angle = getRads(angle);

    return ((velocity * velocity) * sin(2*angle)) / 32.2;
}

/**
* Calculates radians given degrees
*
* radians = (degrees * 3.14159265) / 180.0;
*
* Preconditions: 
*   - degrees are positive 
*
* Postconditions: 
*   - radians are returned
*/
double getRads(double degrees) {
    return (degrees * 3.14159265) / 180.0;
}
