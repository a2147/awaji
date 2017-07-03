//
// Title: Decentralized electrity market on Awaji Island
//
// Project credits: Arkadiusz P. Wojcik
//
// randn_notrig and randn_trig function found on the internet
//
// Mail: arek@wojcik.it
//
// Date: 2013/01/31
//

#include "NormalDistribution.h"

//        "Polar" version without trigonometric calls
double randn_notrig(double mu=0.0, double sigma=1.0) {
        static bool deviateAvailable=false;        //        flag
        static double storedDeviate;                        //        deviate from previous calculation
        double polar, rsquared, var1, var2;
        if (!deviateAvailable) {
                   
                do {
                        var1=2.0*( double(rand())/double(RAND_MAX) ) - 1.0;
                        var2=2.0*( double(rand())/double(RAND_MAX) ) - 1.0;
                        rsquared=var1*var1+var2*var2;
                } while ( rsquared>=1.0 || rsquared == 0.0);
                   
                //        calculate polar tranformation for each deviate
                polar=sqrt(-2.0*log(rsquared)/rsquared);
                   
                //        store first deviate and set flag
                storedDeviate=var1*polar;
                deviateAvailable=true;
                   
                //        return second deviate
                return var2*polar*sigma + mu;
        }
           
        //        If a deviate is available from a previous call to this function, it is
        //        returned, and the flag is set to false.
        else {
                deviateAvailable=false;
                return storedDeviate*sigma + mu;
        }
}
     
  
//        Standard version with trigonometric calls
#define PI 3.14159265358979323846
     
double randn_trig(double mu=0.0, double sigma=1.0) {
        static bool deviateAvailable=false;        //        flag
        static double storedDeviate;                        //        deviate from previous calculation
        double dist, angle;
           
        if (!deviateAvailable) {
                   
                //        choose a pair of uniformly distributed deviates, one for the
                //        distance and one for the angle, and perform transformations
                dist=sqrt( -2.0 * log(double(rand()) / double(RAND_MAX)) );
                angle=2.0 * PI * (double(rand()) / double(RAND_MAX));
                   
                //        calculate and store first deviate and set flag
                storedDeviate=dist*cos(angle);
                deviateAvailable=true;
                   
                //        calcaulate return second deviate
                return dist * sin(angle) * sigma + mu;
        }
           
        //        If a deviate is available from a previous call to this function, it is
        //        returned, and the flag is set to false.
        else {
                deviateAvailable=false;
                return storedDeviate*sigma + mu;
        }
} 