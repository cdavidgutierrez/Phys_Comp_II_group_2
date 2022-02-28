#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>


using namespace std;

    void Shooting(float (*funct)(float,float,float), float (*dfdy)(float,float,float), float (*dfdyp)(float,float,float) , float xMin, float xMax, float yMin, float yMax, int N, float TOL, int maxIter){
    
        //STEP 1.
        float h = (xMax - xMax) / N;
        int k = 1;
        float TK = (yMax - yMin) / (xMax - xMin);
        
        //cout<<((k<=maxIter)==false)<<endl;
        //STEP 2.
        while ((k <= maxIter)!=1){
            cout<<k<<endl;
            //STEP 3.
            float w1_0 = yMin;
            float w2_0 = TK;
            float u1 = 0;
            float u2 = 1;
            
            //***
            vector<float> w1;
            vector<float> w2;
            w1.push_back(w1_0);
            w2.push_back(w2_0);
            
            //STEP 4.
            for (int i = 1; i <= N; i++){
            
                //STEP 5.
                float x = xMin + (i - 1) * h;
                
                //STEP 6.
                float k1_1 = h * w2[i - 1];
                float k1_2 = h * funct(x, w1[i - 1], w2[i - 1]);
                float k2_1 = h * (w2[i - 1] + 0.5 * k1_2);
                float k2_2 = h * funct(x + 0.5 * h, w1[i - 1] + 0.5 * k1_1, w2[i - 1] + 0.5 * k1_2);
                float k3_1 = h * (w2[i - 1] + 0.5 * k2_2);
                float k3_2 = h * funct(x + 0.5 * h, w1[i - 1] + 0.5 * k2_1, w2[i - 1] + 0.5 * k2_2);
                float k4_1 = h * (w2[i - 1] + k3_2);
                float k4_2 = h * funct(x + h, w1[i - 1] + k3_1, w2[i - 1] + k3_2);
                w1.push_back(w1[i - 1] + (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1) / 6);
                w2.push_back(w2[i - 1] + (k1_2 + 2 * k2_2 + 2 * k3_2 + k4_2) / 6);
                
                float kp1_1 = h * u2;
                float kp1_2 = h * (u1 * dfdy(x, w1[i - 1], w2[i - 1]) + u2 * dfdyp(x, w1[i - 1], w2[i - 1]));
                float kp2_1 = h * (u2 + 0.5 * kp1_2);
                float kp2_2 = h * (dfdy(x + 0.5 * h, w1[i - 1], w2[i - 1]) * (u1 + 0.5 * kp1_1)
                                   + dfdyp(x + 0.5 * h, w1[i - 1], w2[i - 1]) * (u2 + 0.5 * kp1_2) 
                                  );
                float kp3_1 = h * (u2 + 0.5 * kp2_2);
                float kp3_2 = h * (dfdy(x + 0.5 * h, w1[i - 1], w2[i - 1]) * (u1 + 0.5 * kp2_1)
                                   + dfdyp(x + 0.5 * h, w1[i - 1], w2[i - 1]) * (u2 + 0.5 * kp2_2) 
                                  ); 
                float kp4_1 = h * (u2 + kp3_2);
                float kp4_2 = h * (dfdy(x + h, w1[i - 1], w2[i - 1]) * (u1 + kp3_1)
                                   + dfdyp(x + h, w1[i - 1], w2[i - 1]) * (u2 + kp3_2) 
                                  );
                u1 += (kp1_1 + 2 * kp2_1 + 2 * kp3_1 + kp4_1) / 6;
                u2 += (kp1_2 + 2 * kp2_2 + 2 * kp3_2 + kp4_2) / 6;
            }
            
            
            //STEP 7.
            if (abs(w1[N] - yMax) <= TOL){
                
                //STEP 8.
                for (int i=0; i <= N; i++){
                
                    float x = xMin + i * h;
                    cout << setw(5) << x << setw(11) << w1[i] << setw(11) << w2[i];
                
                }
                //STEP 9.
                break;
            }
            
            //STEP 10.
            TK -= (w1[N] - yMax) / u1;
            k += 1;
            
        }
        //cout << "Número máximo de iteraciones superado." << endl; 
    
    }

float funct(float _x,float _y, float _yp){
    return (32 + 2 * pow(_x, 3) - _y * _yp) / 8;
}

float dfunct(float _x,float _y, float _yp){
    return -_yp / 8;
}

float dpfunct(float _x,float _y, float _yp){
    return -_y / 8;
}

int main(){
    
    float a = 1;
    float b = 3;
    float alpha = 17;
    float beta = 43/3;
    int N = 20, M = 10;
    float TOL = 0.00001; 
    
    Shooting(*(funct), *(dfunct), *(dpfunct), a, b, alpha, beta, N, TOL, M);
    
    return 0;
}
    
    
    
    
    
    
    
    
    