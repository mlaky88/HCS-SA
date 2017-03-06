#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H
#include "../Algorithm/algorithm.h"

class Cindividual : public Individual
{
private:
    /*any self adaptive parameters*/
    double aLevy;
    double aG;
    double aL;
    double Cr;
    double F;

public:
    Cindividual(int D);

    inline void setAlphaGlobal(double _aG) {aG = _aG;}
    inline void setAlphaLocal(double _aL) {aL = _aL;}
    inline void setAlphaLevy(double _aLevy) {aLevy = _aLevy;}
    inline void setCr(double _Cr) {Cr = _Cr;}
    inline void setF(double _F) {F = _F;}
    inline double get_aG() { return aG;}
    inline double get_aL() { return aL;}
    inline double get_aLevy() {return aLevy;}
    inline double getCr(){ return Cr;}
    inline double getF() {return F;}

    inline static double levyWalk(double c, double alpha, rand_t& rnd)
    {
        static std::uniform_real_distribution<double> uniform01(0,1);
        double u, v, t, s;

        u = M_PI * (uniform01(rnd)-0.5);

        if(alpha == 1) //CAUCHY
        {
            t = tan(u);

            return c*t;
        }

        do
        {
            v = -log(uniform01(rnd));
        } while(v == 0);

        if(alpha == 2) //GAUSSIAN
        {
            t = 2*sin(u)*sqrt(v);

            return c*t;
        }

        //GENERAL CASE
        t = sin(alpha*u) / pow(cos(u), 1/alpha);
        s = pow(cos((1-alpha)*u) / v, (1-alpha)/alpha);

        return c*t*s;
    }

};

#endif //CINDIVIDUAL_H
