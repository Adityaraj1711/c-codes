#include <iostream>
#include <math.h>
#include <graphics.h>
using namespace std;
const float mul = 180 / 3.14;
#define SIN(x) sin(x * 3.141592653589/180)
#define COS(x) cos(x * 3.141592653589/180)

void translateRectangle (int rec_coor[][2], int translate_x, int translate_y)
{
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL);
 
    int x1 = rec_coor[0][0] + translate_x;
    int y1 = rec_coor[0][1] + translate_y;
    int x2 = rec_coor[1][0] + translate_x;
    int y2 = rec_coor[1][1] + translate_y;
 
    setcolor(3);
    rectangle (x1, y1, x2, y2);
    
    getch();
}

void scaleRectangle (int rec_coor[][2], int scale_x, int scale_y)
{
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL); 
 
    int x1 = rec_coor[0][0];
    int y1 = rec_coor[0][1];
    int x2 = rec_coor[1][0] * scale_x - rec_coor[0][0];
    int y2 = rec_coor[1][1] * scale_y - rec_coor[0][1];
    //int x2 = rec_coor[1][0]*scale_x;
    //int y2 = rec_coor[1][1]*scale_y;
    setcolor(4);
    rectangle (x1, y1, x2, y2);
    
    getch();
}

void rotateRectangle1 (int rec_coor[][2], int rotate)
{
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL); 
    int x1 = rec_coor[0][0];
    int y1 = rec_coor[0][1];
    int x2 = rec_coor[0][0];
    int y2 = rec_coor[1][1];
    int x3 = rec_coor[1][0];
    int y3 = rec_coor[1][1];
    int x4 = rec_coor[1][0];
    int y4 = rec_coor[0][1];
    
    float theta = rotate * mul;
    setcolor(3);
    line(x1,y1,x2,y2);
    line(x2,y2,x3,y3);
    line(x3,y3,x4,y4);
    line(x4,y4,x1,y1);
    int x11 = x1 * cos(theta) - y1 * sin(theta);
    int y11 = x1 * sin(theta) + y1 * cos(theta);
    int x12 = x2 * cos(theta) - y2 * sin(theta);
    int y12 = x2 * sin(theta) + y2 * cos(theta);
    int x13 = x3 * cos(theta) - y3 * sin(theta);
    int y13 = x3 * sin(theta) + y3 * cos(theta);
    int x14 = x4 * cos(theta) - y4 * sin(theta);
    int y14 = x4 * sin(theta) + y4 * cos(theta);
   
    setcolor(2);
    putpixel(x11,y11,2);
    
    //cout<<" x1 "<<x1<<" y1 "<<y1<<" x2 "<<x2<<" y2 "<<y2;
    line(x11,y11,x12,y12);
   
    
    getch();
    closegraph();
}
void rotate(int rec_coor[][2], int angle)
{   int gd = DETECT, gm;
    int x_pivot = 100;
    int y_pivot = 100;
    float a[4][2];
    initgraph (&gd, &gm, NULL); 
    a[0][0] = rec_coor[0][0];
    a[0][1] = rec_coor[0][1];
    a[1][0] = rec_coor[0][0];
    a[1][1] = rec_coor[1][1];
    a[2][0] = rec_coor[1][0];
    a[2][1] = rec_coor[1][1];
    a[3][0] = rec_coor[1][0];
    a[3][1] = rec_coor[0][1];
    
    int n = 4;
    int i = 0;
    while (i < n)
    {
        // Shifting the pivot point to the origin
        // and the given points accordingly
        int x_shifted = a[i][0] - x_pivot;
        int y_shifted = a[i][1] - y_pivot;
 
        // Calculating the rotated point co-ordinates
        // and shifting it back
        a[i][0] = x_pivot + (x_shifted*COS(angle) 
                          - y_shifted*SIN(angle));
        a[i][1] = y_pivot + (x_shifted*SIN(angle) 
                          + y_shifted*COS(angle));
        printf("(%f, %f) ", a[i][0], a[i][1]);
        i++;
    }
    setcolor(4);
    line(a[0][0],a[0][1],a[1][0],a[1][1]);
    line(a[1][0],a[1][1],a[2][0],a[2][1]);
    line(a[2][0],a[2][1],a[3][0],a[3][1]);
    line(a[3][0],a[3][1],a[0][0],a[0][1]);
    getch();
    closegraph();
}
int main()
{
    int rec_coor[2][2] = {100, 100, 200, 200};
    
    int gd = DETECT, gm;
    initgraph (&gd, &gm, NULL); 
    
    setcolor(2);
    rectangle (rec_coor[0][0], rec_coor[0][1], rec_coor[1][0], rec_coor[1][1]);
    getch();
    
    int translate_x = 100, translate_y = 150;
    translateRectangle(rec_coor, translate_x, translate_y);
    
    int scale_x = 2, scale_y = 2;
    scaleRectangle(rec_coor, scale_x, scale_y);
    
    setcolor(2);
    //line(rec_coor[0][0], rec_coor[0][1], rec_coor[1][0], rec_coor[1][1]);
    int angle = 10;
    rotate(rec_coor, angle);
    return 0;
} 
