#include <stdio.h>
#include <string.h>
#include <math.h>
#define pi 3.1415926535896932846

const float r1 = 1, r2 = 2, k2 = 2;
const int screen_width = 1920, screen_height = 1080;
const float theta_spacing = 0.07, phi_spacing = 0.02;

void RenderFrame(int A, int B);

int main(){
    
    float A=0, B=0;

    for(int i=0; i<1920; i++){
        RenderFrame(A, B);
        A += 0.07;
        B += 0.04;
    }
    int x;
    scanf("%i", &x);
    return 0;
}


void RenderFrame(int A, int B)
{
    float k1 = screen_width * k2 * 3 / (8 * (r1 + r2));
    char char_output[screen_height][screen_width];
    printf("hi");
    float zbuffer[screen_height][screen_width];
    printf("hi");

    for (int i = 0; i < screen_height; i++) {
        for(int j = 0; j< screen_width; j++){
            char_output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }

    float cosA = cos(A), sinA = sin(A);
    float cosB = cos(B), sinB = sin(B);
    
    printf("%lf", pi);
    for (int tetha; tetha<=pi*2; tetha += theta_spacing) {

        float costetha = cos(tetha);
        float sintetha = sin(tetha);

        for (int phi; phi <= pi*2; phi += phi_spacing) {
            float cosphi = cos(phi), sinphi = sin(phi);

            float cx = r1 + r2 * costetha;
            float cy = r1 * sintetha;

            float x = cx * ( cosB * cosphi + sinA * sinB * sinphi) - cy * cosA * sinB;
            float y = cx * (cosphi * sinB - cosB * sinA * sinphi) + cy * cosA * cosB;
            float z = k2 + cosA * cx * sinphi + cy * sinA;
            float zn = 1 / z;

            int xp = (int)(screen_width/2 + k1 * zn * x);
            int yp = (int)(screen_height/2 - k1 * zn * y); 

            // Calculate luminance; 
            
            float L = cosphi * costetha * sinB - cosA * costetha * sinphi - sinA * sintetha + cosB * (cosA * sintetha - costetha * sinA * sinphi);

            if (L>0) {
                if (zn > zbuffer[xp][yp]){
                    zbuffer[xp][yp] = zn;
                    int luminance_index = L*8;

                    char_output[xp][yp] = ".,-:;=!*#$@"[(int)(luminance_index)];
                }        
            }
        }
    }

    printf("\x1b[H");
    for(int i = 0; i<screen_height; i++)
    {
        for(int j = 0; j < screen_width; j++){
            printf("%c", char_output[i][j]);
        }
        putchar('\n');
    }

}


