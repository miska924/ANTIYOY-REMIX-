#ifndef _PRIMITIVES
#define _PRIMITIVES

void drawCircle     (double x, double y, double r,               double color = 0, double z = 0.1);
void drawCircleEmpty(double x, double y, double r,               double color = 0, double z = 0.1);
void drawLine       (double x0, double y0, double x1, double y1, double color = 0, double z = 0.1);
void drawCrown      (double x, double y, double r                                , double z = 0.1);
void drawSword      (double x0, double y0, double x1, double y1, double color = 0, double z = 0.05);
void drawSquare     (double x, double y, double r,               double color = 0, double z = 0.1);

#endif