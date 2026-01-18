#include <cstdio>
#include <windows.h>
#include <math.h>
#include <cstdlib>
#define PI 3.14159265358979323846
#include <GL/gl.h>
#include <GL/glut.h>
#include <MMSystem.h>

// Forward declarations
void PointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec);
void drawBoatman(float x, float y, float scale);

void PointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec)
{
    glEnable(GL_LIGHTING);
    GLfloat light_ambient[] = {amb, amb, amb, 1.0};
    GLfloat light_position[] = {-0.9, .9, 0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0); // enable the light after setting the properties
}
GLfloat position22 = 0.0f;
GLfloat speed22 = 0.007f;

// Wing animation variables
GLfloat wingAngle = 0.0f;
GLfloat wingSpeed = 0.15f;
int wingDirection = 1;

// Lightning effect variables for rain scene
bool lightningActive = false;
int lightningTimer = 0;
float lightningBrightness = 0.0f;
int lightningCooldown = 0;

// Bird structure for dynamic birds
struct Bird {
    float x, y;           // position
    float speed;          // horizontal speed
    float wingPhase;      // wing animation phase offset
    float scale;          // size scale
    float verticalOffset; // for slight up/down movement
    float verticalSpeed;  // vertical oscillation speed
};

// Create multiple birds with different properties
Bird birds[6] = {
    {-0.8f, 0.82f, 0.008f, 0.0f, 1.0f, 0.0f, 0.02f},
    {-0.4f, 0.78f, 0.006f, 1.5f, 0.85f, 0.0f, 0.025f},
    {0.0f, 0.85f, 0.007f, 3.0f, 0.95f, 0.0f, 0.018f},
    {0.3f, 0.80f, 0.009f, 2.0f, 0.9f, 0.0f, 0.022f},
    {0.6f, 0.75f, 0.005f, 4.0f, 1.1f, 0.0f, 0.015f},
    {-0.2f, 0.88f, 0.0065f, 2.5f, 0.8f, 0.0f, 0.02f}
};

void birdd(int value)
{
    // Update horizontal position for all birds
    for (int i = 0; i < 6; i++) {
        birds[i].x += birds[i].speed;
        if (birds[i].x > 1.3f) {
            birds[i].x = -1.3f;
            // Randomize Y position slightly when bird reappears
            birds[i].y = 0.75f + (float)(rand() % 15) / 100.0f;
        }
        // Update vertical oscillation
        birds[i].verticalOffset = 0.02f * sin(wingAngle * 0.5f + birds[i].wingPhase);
    }
    
    // Update wing animation
    wingAngle += wingSpeed * wingDirection;
    if (wingAngle > 0.8f || wingAngle < -0.3f) {
        wingDirection *= -1;
    }
    
    position22 += speed22;
    if (position22 > 1.0f) position22 = -1.0f;
    
    glutPostRedisplay();
    glutTimerFunc(16, birdd, 0);  // ~60 FPS for smooth animation
}
GLfloat position4 = 0.0f;
GLfloat speed4 = -0.01f;
void sunn(int value)
{
    if (position4 > 1.0)
        position4 = 0.0f;

    position4 += speed4;

    glutPostRedisplay();

    glutTimerFunc(100, sunn, 0);
}
GLfloat position3 = 0.0f;
GLfloat speed3 = -0.5f;
void rain(int value)
{
    if (position3 < -1.0)
        position3 = 1.0f;
    position3 += speed3;
    
    // Lightning effect logic
    if (lightningCooldown > 0) {
        lightningCooldown--;
    }
    
    if (lightningActive) {
        lightningTimer--;
        if (lightningTimer <= 0) {
            lightningActive = false;
            lightningBrightness = 0.0f;
            lightningCooldown = 30 + rand() % 50; // Random cooldown before next lightning
        } else {
            // Flickering effect
            if (lightningTimer > 8) {
                lightningBrightness = 0.8f + 0.2f * (float)(rand() % 100) / 100.0f;
            } else {
                lightningBrightness = (float)lightningTimer / 10.0f;
            }
        }
    } else if (lightningCooldown <= 0 && rand() % 100 < 3) {
        // Random chance to trigger lightning
        lightningActive = true;
        lightningTimer = 8 + rand() % 6;
        lightningBrightness = 1.0f;
    }
    
    glutPostRedisplay();
    glutTimerFunc(100, rain, 0);
}
GLfloat position2 = 0.0f;
GLfloat speed2 = 0.004f;
void cloud(int value)
{
    if (position2 > 1.0)
        position2 = -1.0f;
    position2 += speed2;
    glutPostRedisplay();
    glutTimerFunc(100, cloud, 0);
}
GLfloat position1 = 1.0f;
GLfloat speed1 = -0.005f;
void boat(int value)
{
    if (position1 < -1.0)
        position1 = 1.0f;

    position1 += speed1;

    glutPostRedisplay();

    glutTimerFunc(100, boat, 0);
}
void cloud1()
{
    int i;

    GLfloat x = .5f;
    GLfloat y = .86f;
    GLfloat radius = .05f;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat a = .55f;
    GLfloat b = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(a, b); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            a + (radius * cos(i * twicePi / triangleAmount)),
            b + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat c = .45f;
    GLfloat d = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(c, d); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            c + (radius * cos(i * twicePi / triangleAmount)),
            d + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat e = .52f;
    GLfloat f = .8f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(e, f); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            e + (radius * cos(i * twicePi / triangleAmount)),
            f + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat g = .6f;
    GLfloat h = .82f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(g, h); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            g + (radius * cos(i * twicePi / triangleAmount)),
            h + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}

void cloud2()
{
    // glLoadIdentity();
    int i;

    GLfloat x = -.5f;
    GLfloat y = .86f;
    GLfloat radius = .05f;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat a = -.55f;
    GLfloat b = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(a, b); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            a + (radius * cos(i * twicePi / triangleAmount)),
            b + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat c = -.45f;
    GLfloat d = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(c, d); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            c + (radius * cos(i * twicePi / triangleAmount)),
            d + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat e = -.52f;
    GLfloat f = .8f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(e, f); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            e + (radius * cos(i * twicePi / triangleAmount)),
            f + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat g = -.6f;
    GLfloat h = .82f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(g, h); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            g + (radius * cos(i * twicePi / triangleAmount)),
            h + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}
void cloud3()
{
    // glLoadIdentity();
    int i;

    GLfloat x = 0.0f;
    GLfloat y = .86f;
    GLfloat radius = .05f;
    int triangleAmount = 20;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat a = .05f;
    GLfloat b = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(a, b); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            a + (radius * cos(i * twicePi / triangleAmount)),
            b + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat c = -0.05f;
    GLfloat d = .83f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(c, d); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            c + (radius * cos(i * twicePi / triangleAmount)),
            d + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat e = .02f;
    GLfloat f = .8f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(e, f); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            e + (radius * cos(i * twicePi / triangleAmount)),
            f + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

    GLfloat g = .1f;
    GLfloat h = .82f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 217, 255);
    glVertex2f(g, h); // center of circle
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            g + (radius * cos(i * twicePi / triangleAmount)),
            h + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
}
void sky()
{
    glBegin(GL_QUADS);
    glColor3ub(51, 204, 255);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(1.0f, 0.45f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}
void sky2()
{
    glBegin(GL_QUADS);
    glColor3ub(0, 51, 204);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(1.0f, 0.45f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();
}

// Rain sky with dark storm clouds and lightning
void skyRain()
{
    // Dark stormy sky gradient
    glBegin(GL_QUADS);
    // Upper dark
    glColor3ub((int)(30 + lightningBrightness * 80), (int)(35 + lightningBrightness * 85), (int)(50 + lightningBrightness * 100));
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    // Lower slightly lighter
    glColor3ub((int)(50 + lightningBrightness * 100), (int)(55 + lightningBrightness * 110), (int)(70 + lightningBrightness * 120));
    glVertex2f(1.0f, 0.45f);
    glVertex2f(-1.0f, 0.45f);
    glEnd();
    
    // Draw lightning bolt when active
    if (lightningActive && lightningBrightness > 0.3f) {
        glLineWidth(4);
        glBegin(GL_LINE_STRIP);
        glColor4f(1.0f, 1.0f, 0.9f, lightningBrightness);
        // Main bolt
        glVertex2f(0.2f, 1.0f);
        glVertex2f(0.15f, 0.85f);
        glVertex2f(0.25f, 0.8f);
        glVertex2f(0.18f, 0.65f);
        glVertex2f(0.28f, 0.6f);
        glVertex2f(0.2f, 0.48f);
        glEnd();
        
        // Branch 1
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        glColor4f(1.0f, 1.0f, 0.85f, lightningBrightness * 0.8f);
        glVertex2f(0.25f, 0.8f);
        glVertex2f(0.35f, 0.72f);
        glVertex2f(0.32f, 0.65f);
        glEnd();
        
        // Branch 2
        glBegin(GL_LINE_STRIP);
        glColor4f(1.0f, 1.0f, 0.85f, lightningBrightness * 0.7f);
        glVertex2f(0.18f, 0.65f);
        glVertex2f(0.08f, 0.58f);
        glEnd();
        
        // Glow effect around bolt
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(12);
        glBegin(GL_LINE_STRIP);
        glColor4f(0.8f, 0.85f, 1.0f, lightningBrightness * 0.3f);
        glVertex2f(0.2f, 1.0f);
        glVertex2f(0.15f, 0.85f);
        glVertex2f(0.25f, 0.8f);
        glVertex2f(0.18f, 0.65f);
        glVertex2f(0.28f, 0.6f);
        glVertex2f(0.2f, 0.48f);
        glEnd();
        glDisable(GL_BLEND);
    }
}

// Function to draw rain puddles with ripples
void drawRainPuddles()
{
    int i;
    GLfloat twicePi = 2.0f * PI;
    
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Puddle 1
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(100, 120, 150, 100);
    glVertex2f(-0.3f, -0.52f);
    for (i = 0; i <= 20; i++) {
        glVertex2f(-0.3f + 0.08f * cos(i * twicePi / 20), -0.52f + 0.02f * sin(i * twicePi / 20));
    }
    glEnd();
    
    // Ripple effect
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor4ub(180, 200, 220, 150);
    for (i = 0; i <= 16; i++) {
        glVertex2f(-0.3f + 0.04f * cos(i * twicePi / 16), -0.52f + 0.01f * sin(i * twicePi / 16));
    }
    glEnd();
    
    // Puddle 2
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(90, 110, 140, 90);
    glVertex2f(0.4f, -0.65f);
    for (i = 0; i <= 20; i++) {
        glVertex2f(0.4f + 0.1f * cos(i * twicePi / 20), -0.65f + 0.025f * sin(i * twicePi / 20));
    }
    glEnd();
    
    // Ripple
    glBegin(GL_LINE_LOOP);
    glColor4ub(170, 190, 210, 140);
    for (i = 0; i <= 16; i++) {
        glVertex2f(0.4f + 0.05f * cos(i * twicePi / 16), -0.65f + 0.012f * sin(i * twicePi / 16));
    }
    glEnd();
    
    // Puddle 3
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(95, 115, 145, 95);
    glVertex2f(-0.7f, -0.75f);
    for (i = 0; i <= 20; i++) {
        glVertex2f(-0.7f + 0.06f * cos(i * twicePi / 20), -0.75f + 0.015f * sin(i * twicePi / 20));
    }
    glEnd();
    
    glDisable(GL_BLEND);
}

void backgroundtree()
{
    // pamtrees
    glBegin(GL_POLYGON);
    glColor3ub(102, 51, 0);
    glVertex2f(-0.52f, 0.45f);
    glVertex2f(-0.48f, 0.45f);
    glVertex2f(-0.48f, 0.62f);
    glVertex2f(-0.5f, 0.64f);
    glVertex2f(-0.52f, 0.62f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(-0.5f, 0.64f);
    glVertex2f(-0.52f, 0.62f);
    glVertex2f(-0.58f, 0.6f);
    glVertex2f(-0.55f, 0.63f);
    glVertex2f(-0.58f, 0.66f);
    glVertex2f(-0.52f, 0.66f);
    glVertex2f(-0.52f, 0.72f);
    glVertex2f(-0.5f, 0.69f); ///
    glVertex2f(-0.48f, 0.72f);
    glVertex2f(-0.48f, 0.66f);
    glVertex2f(-0.42f, 0.66f);
    glVertex2f(-0.45f, 0.63f);
    glVertex2f(-0.42f, 0.6f);
    glVertex2f(-0.48f, 0.62f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(102, 51, 0);
    glVertex2f(0.52f, 0.45f);
    glVertex2f(0.48f, 0.45f);
    glVertex2f(0.48f, 0.62f);
    glVertex2f(0.5f, 0.64f);
    glVertex2f(0.52f, 0.62f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(0.5f, 0.64f);
    glVertex2f(0.52f, 0.62f);
    glVertex2f(0.58f, 0.6f);
    glVertex2f(0.55f, 0.63f);
    glVertex2f(0.58f, 0.66f);
    glVertex2f(0.52f, 0.66f);
    glVertex2f(0.52f, 0.72f);
    glVertex2f(0.5f, 0.69f); ///
    glVertex2f(0.48f, 0.72f);
    glVertex2f(0.48f, 0.66f);
    glVertex2f(0.42f, 0.66f);
    glVertex2f(0.45f, 0.63f);
    glVertex2f(0.42f, 0.6f);
    glVertex2f(0.48f, 0.62f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(-1.0f, 0.45f);
    glVertex2f(-0.98f, 0.5f);
    glVertex2f(-0.93f, 0.56);
    glVertex2f(-0.9f, 0.6f);
    glVertex2f(-0.82f, 0.64);
    glVertex2f(-0.75f, 0.67); ///
    glVertex2f(-0.68f, 0.64);
    glVertex2f(-0.6f, 0.6f);
    glVertex2f(-0.57f, 0.56);
    glVertex2f(-0.52f, 0.5f);
    glVertex2f(-0.5f, 0.45f);
    glVertex2f(-1.0f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(1.0f, 0.45f);
    glVertex2f(0.98f, 0.5f);
    glVertex2f(0.93f, 0.56);
    glVertex2f(0.9f, 0.6f);
    glVertex2f(0.82f, 0.64);
    glVertex2f(0.75f, 0.67); ///
    glVertex2f(0.68f, 0.64);
    glVertex2f(0.6f, 0.6f);
    glVertex2f(0.57f, 0.56);
    glVertex2f(0.52f, 0.5f);
    glVertex2f(0.5f, 0.45f);
    glVertex2f(1.0f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(-0.5f, 0.45f);
    glVertex2f(-0.48f, 0.5f);
    glVertex2f(-0.45f, 0.56);
    glVertex2f(-0.42f, 0.6f);
    glVertex2f(-0.37f, 0.62); ///
    glVertex2f(-0.32f, 0.6);
    glVertex2f(-0.29f, 0.56f);
    glVertex2f(-0.27f, 0.5f);
    glVertex2f(-0.25f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(0.5f, 0.45f);
    glVertex2f(0.48f, 0.5f);
    glVertex2f(0.45f, 0.56);
    glVertex2f(0.42f, 0.6f);
    glVertex2f(0.37f, 0.62); ///
    glVertex2f(0.32f, 0.6);
    glVertex2f(0.29f, 0.56f);
    glVertex2f(0.27f, 0.5f);
    glVertex2f(0.25f, 0.45f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(34, 139, 34);
    glVertex2f(-.25f, 0.45f);
    glVertex2f(-0.23f, 0.5f);
    glVertex2f(-0.18f, 0.56);
    glVertex2f(-0.15f, 0.6f);
    glVertex2f(-0.07f, 0.64);
    glVertex2f(-0.00f, 0.67); ///
    glVertex2f(0.07f, 0.64);
    glVertex2f(0.15f, 0.6f);
    glVertex2f(0.18f, 0.56);
    glVertex2f(0.23f, 0.5f);
    glVertex2f(.25f, 0.45f);
    glEnd();
}
// Draw a single realistic bird with animated wings at position (x, y)
void drawSingleBird(float x, float y, float scale, float wingPhase)
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    
    // Calculate wing angle for this bird (with phase offset for variety)
    float currentWingAngle = wingAngle + wingPhase;
    float wingY = sin(currentWingAngle * 3.0f) * 0.035f * scale;  // Wing flap amplitude
    float wingY2 = sin(currentWingAngle * 3.0f + 0.5f) * 0.025f * scale;  // Secondary feathers
    
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    
    // === BIRD BODY (streamlined oval shape) ===
    GLfloat bodyRadius = 0.018f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(45, 45, 50);  // Dark gray body
    glVertex2f(0.0f, 0.0f);
    for (i = 0; i <= triangleAmount; i++)
    {
        float angle = i * twicePi / triangleAmount;
        glVertex2f(bodyRadius * 1.8f * cos(angle), bodyRadius * sin(angle));
    }
    glEnd();
    
    // === BIRD HEAD ===
    GLfloat headRadius = 0.012f;
    float headX = 0.025f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(35, 35, 40);  // Slightly darker head
    glVertex2f(headX, 0.003f);
    for (i = 0; i <= triangleAmount; i++)
    {
        float angle = i * twicePi / triangleAmount;
        glVertex2f(headX + headRadius * cos(angle), 0.003f + headRadius * sin(angle));
    }
    glEnd();
    
    // === BEAK ===
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 180, 50);  // Orange beak
    glVertex2f(headX + 0.012f, 0.005f);
    glVertex2f(headX + 0.012f, 0.0f);
    glVertex2f(headX + 0.022f, 0.002f);
    glEnd();
    
    // === EYE ===
    glPointSize(2.0f * scale);
    glBegin(GL_POINTS);
    glColor3ub(255, 255, 255);
    glVertex2f(headX + 0.005f, 0.006f);
    glEnd();
    
    // === TAIL FEATHERS ===
    glBegin(GL_TRIANGLES);
    glColor3ub(30, 30, 35);
    glVertex2f(-0.025f, 0.0f);
    glVertex2f(-0.045f, 0.012f);
    glVertex2f(-0.04f, 0.0f);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3ub(40, 40, 45);
    glVertex2f(-0.025f, 0.0f);
    glVertex2f(-0.042f, -0.008f);
    glVertex2f(-0.038f, 0.0f);
    glEnd();
    
    // === LEFT WING (animated) ===
    glBegin(GL_POLYGON);
    glColor3ub(55, 55, 60);  // Wing base color
    glVertex2f(-0.005f, 0.005f);  // Wing attachment point
    glVertex2f(-0.015f, 0.015f + wingY * 0.5f);
    glVertex2f(-0.025f, 0.035f + wingY);  // Wing tip (animated)
    glVertex2f(-0.01f, 0.025f + wingY * 0.7f);
    glVertex2f(0.005f, 0.015f + wingY * 0.3f);
    glVertex2f(0.01f, 0.005f);
    glEnd();
    
    // Wing feather details (left)
    glBegin(GL_LINES);
    glColor3ub(70, 70, 75);
    glVertex2f(-0.008f, 0.01f + wingY * 0.4f);
    glVertex2f(-0.02f, 0.03f + wingY * 0.9f);
    glVertex2f(-0.003f, 0.01f + wingY * 0.3f);
    glVertex2f(-0.015f, 0.028f + wingY * 0.85f);
    glEnd();
    
    // === RIGHT WING (animated - mirrored) ===
    glBegin(GL_POLYGON);
    glColor3ub(50, 50, 55);  // Slightly different shade
    glVertex2f(-0.005f, -0.005f);  // Wing attachment point
    glVertex2f(-0.015f, -0.015f - wingY * 0.5f);
    glVertex2f(-0.025f, -0.032f - wingY);  // Wing tip (animated)
    glVertex2f(-0.01f, -0.022f - wingY * 0.7f);
    glVertex2f(0.005f, -0.012f - wingY * 0.3f);
    glVertex2f(0.01f, -0.005f);
    glEnd();
    
    // Wing feather details (right)
    glBegin(GL_LINES);
    glColor3ub(65, 65, 70);
    glVertex2f(-0.008f, -0.01f - wingY * 0.4f);
    glVertex2f(-0.02f, -0.027f - wingY * 0.9f);
    glVertex2f(-0.003f, -0.01f - wingY * 0.3f);
    glVertex2f(-0.015f, -0.025f - wingY * 0.85f);
    glEnd();
    
    // === CHEST HIGHLIGHT ===
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(75, 75, 80);  // Lighter chest
    glVertex2f(0.01f, 0.0f);
    for (i = 0; i <= 8; i++)
    {
        float angle = i * PI / 8 - PI/2;
        glVertex2f(0.01f + 0.008f * cos(angle), 0.006f * sin(angle));
    }
    glEnd();
    
    glPopMatrix();
}

// Draw all birds with animation
void bird()
{
    for (int i = 0; i < 6; i++) {
        float yPos = birds[i].y + birds[i].verticalOffset;
        drawSingleBird(birds[i].x, yPos, birds[i].scale, birds[i].wingPhase);
    }
}
void stars()
{
    glPointSize(2.5);
    glBegin(GL_POINTS);
    glColor3ub(255, 255, 255);
    glVertex2f(0.8f, 0.95f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(0.95f, 0.7f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.7f, 0.9f);
    glVertex2f(0.6f, 0.8f);
    glVertex2f(0.5f, 0.75f);
    glVertex2f(0.4f, 0.9f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.25f, 0.9f);
    glVertex2f(0.25f, 0.7f);
    glVertex2f(0.1f, 0.9f);
    glVertex2f(0.15f, 0.75f);
    glVertex2f(0.0f, 0.8f);
    glVertex2f(-0.7f, 0.9f);
    glVertex2f(-0.8f, 0.95f);
    glVertex2f(-0.4f, 0.8f);
    glVertex2f(-0.8f, 0.95f);
    glVertex2f(-0.9f, 0.9f);
    glVertex2f(-0.95f, 0.7f);
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(-0.7f, 0.9f);
    glVertex2f(-0.6f, 0.8f);
    glVertex2f(-0.5f, 0.75f);
    glVertex2f(-0.4f, 0.9f);
    glVertex2f(-0.3f, 0.7f);
    glVertex2f(-0.25f, 0.9f);
    glVertex2f(-0.25f, 0.7f);
    glVertex2f(-0.15f, 0.75f);
    glVertex2f(-0.1f, 0.9f);
    glEnd();
}
void sun()
{
    int i;
    int triangleAmount = 32;
    GLfloat twicePi = 2.0f * PI;
    
    GLfloat x = 0.0f;
    GLfloat y = 0.9f;
    GLfloat radius = 0.08f;
    
    // === OUTER GLOW (soft light effect) ===
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(255, 220, 100, 80);  // Soft yellow glow
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glColor4ub(255, 200, 50, 0);  // Fade to transparent
        glVertex2f(x + 0.18f * cos(i * twicePi / triangleAmount),
                   y + 0.18f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // === SUNRAYS ===
    glLineWidth(3);
    for (i = 0; i < 12; i++) {
        float angle = i * twicePi / 12;
        float innerR = 0.09f;
        float outerR = 0.14f + 0.02f * sin(i * 2);  // Varying ray lengths
        
        glBegin(GL_LINES);
        glColor3ub(255, 200, 50);
        glVertex2f(x + innerR * cos(angle), y + innerR * sin(angle));
        glColor3ub(255, 230, 100);
        glVertex2f(x + outerR * cos(angle), y + outerR * sin(angle));
        glEnd();
    }
    
    // === MAIN SUN BODY ===
    // Outer ring (orange)
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 180, 0);
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + radius * cos(i * twicePi / triangleAmount),
                   y + radius * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // Inner bright core
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 200);  // Bright white-yellow center
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glColor3ub(255, 220, 50);
        glVertex2f(x + 0.05f * cos(i * twicePi / triangleAmount),
                   y + 0.05f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // Highlight spot
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    glVertex2f(x - 0.02f, y + 0.025f);
    for (i = 0; i <= 12; i++) {
        glColor3ub(255, 255, 200);
        glVertex2f(x - 0.02f + 0.015f * cos(i * twicePi / 12),
                   y + 0.025f + 0.012f * sin(i * twicePi / 12));
    }
    glEnd();
}

void moon()
{
    int i;
    int triangleAmount = 32;
    GLfloat twicePi = 2.0f * PI;
    
    GLfloat x = -0.5f;
    GLfloat y = 0.9f;
    GLfloat radius = 0.07f;
    
    // === MOON GLOW (ambient light) ===
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(200, 220, 255, 60);
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glColor4ub(150, 180, 220, 0);
        glVertex2f(x + 0.15f * cos(i * twicePi / triangleAmount),
                   y + 0.15f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // === MAIN MOON (crescent effect) ===
    // Full moon base
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(240, 245, 255);  // Pale white-blue
    glVertex2f(x, y);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + radius * cos(i * twicePi / triangleAmount),
                   y + radius * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // Shadow for crescent effect
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(25, 35, 60);  // Dark sky color
    glVertex2f(x + 0.03f, y + 0.01f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(x + 0.03f + 0.055f * cos(i * twicePi / triangleAmount),
                   y + 0.01f + 0.055f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // === MOON SURFACE DETAILS (craters) ===
    // Crater 1
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(210, 215, 230);
    glVertex2f(x - 0.025f, y + 0.015f);
    for (i = 0; i <= 12; i++) {
        glVertex2f(x - 0.025f + 0.012f * cos(i * twicePi / 12),
                   y + 0.015f + 0.01f * sin(i * twicePi / 12));
    }
    glEnd();
    
    // Crater 2
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(215, 220, 235);
    glVertex2f(x - 0.04f, y - 0.02f);
    for (i = 0; i <= 10; i++) {
        glVertex2f(x - 0.04f + 0.008f * cos(i * twicePi / 10),
                   y - 0.02f + 0.007f * sin(i * twicePi / 10));
    }
    glEnd();
    
    // Crater 3
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(220, 225, 240);
    glVertex2f(x - 0.015f, y - 0.035f);
    for (i = 0; i <= 10; i++) {
        glVertex2f(x - 0.015f + 0.01f * cos(i * twicePi / 10),
                   y - 0.035f + 0.008f * sin(i * twicePi / 10));
    }
    glEnd();
    
    // Moon highlight
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 255);
    glVertex2f(x - 0.035f, y + 0.035f);
    for (i = 0; i <= 10; i++) {
        glColor3ub(245, 250, 255);
        glVertex2f(x - 0.035f + 0.012f * cos(i * twicePi / 10),
                   y + 0.035f + 0.01f * sin(i * twicePi / 10));
    }
    glEnd();
}

void ground()
{
    // Main ground with gradient shading
    glBegin(GL_POLYGON);
    // Darker at edges for depth/shadow effect
    glColor3ub(85, 200, 45);
    glVertex2f(-1.0f, -1.0f);
    glColor3ub(90, 210, 48);
    glVertex2f(-1.0f, 0.0f);
    // Brighter in the middle (sun-lit area)
    glColor3ub(115, 255, 60);
    glVertex2f(0.0f, 0.0f);
    glColor3ub(110, 250, 55);
    glVertex2f(0.1f, -0.03);
    glVertex2f(0.2f, -0.07);
    glColor3ub(105, 245, 52);
    glVertex2f(0.3f, -0.1);
    glVertex2f(0.2f, -0.13);
    glVertex2f(0.1f, -0.17);
    glColor3ub(100, 235, 50);
    glVertex2f(0.2f, -0.2);
    glVertex2f(0.35f, -0.23);
    glVertex2f(0.25f, -0.25);
    glColor3ub(95, 225, 48);
    glVertex2f(0.18f, -0.28);
    glVertex2f(0.3f, -0.32);
    glVertex2f(0.2f, -0.35);
    glColor3ub(90, 215, 45);
    glVertex2f(0.4f, -0.4);
    glVertex2f(0.4f, -0.6);
    glColor3ub(85, 205, 42);
    glVertex2f(0.2f, -0.65);
    glVertex2f(0.3f, -0.7);
    glColor3ub(80, 195, 40);
    glVertex2f(0.2f, -0.75);
    glVertex2f(0.4f, -0.8);
    glColor3ub(75, 185, 38);
    glVertex2f(0.2f, -0.85);
    glVertex2f(0.35f, -0.9);
    glColor3ub(70, 175, 35);
    glVertex2f(0.25f, -0.95);
    glVertex2f(0.4f, -1.0);
    glEnd();
    
    // Add subtle grass texture lines for depth
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor4ub(60, 140, 30, 100);
    for (float y = -0.9f; y < -0.1f; y += 0.15f) {
        for (float x = -0.9f; x < -0.1f; x += 0.08f) {
            glVertex2f(x, y);
            glVertex2f(x + 0.01f, y + 0.03f);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.17f, -0.19);
    glVertex2f(0.19f, -0.2f);
    glVertex2f(0.3f, -0.12f);
    glVertex2f(0.3f, -0.1);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.23f, -0.295);
    glVertex2f(0.25f, -0.305f);
    glVertex2f(0.35f, -0.25f);
    glVertex2f(0.35f, -0.23);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.3f, -0.32);
    glVertex2f(0.3f, -0.34);
    glVertex2f(0.25f, -0.365f);
    glVertex2f(0.2f, -0.35);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.205f, -0.655);
    glVertex2f(0.4f, -0.6);
    glVertex2f(0.4f, -0.625);
    glVertex2f(0.25f, -0.675);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.3f, -0.7);
    glVertex2f(0.3f, -0.72);
    glVertex2f(0.24f, -0.7595);
    glVertex2f(0.2f, -0.75);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.4f, -0.8);
    glVertex2f(0.4f, -0.825);
    glVertex2f(0.24f, -0.865);
    glVertex2f(0.2f, -0.85);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(0.35f, -0.9);
    glVertex2f(0.35f, -0.925);
    glVertex2f(0.27f, -0.958);
    glVertex2f(0.25f, -0.948);
    glEnd();
}
void river()
{
    // River with depth shading and reflection effect
    glBegin(GL_QUADS);
    // Darker at edges (deeper water effect)
    glColor3ub(25, 100, 160);
    glVertex2f(-1.0f, 0.45f);
    glColor3ub(25, 100, 160);
    glVertex2f(1.0f, 0.45f);
    // Lighter in middle (sky reflection)
    glColor3ub(50, 170, 230);
    glVertex2f(1.0f, -1.0f);
    glColor3ub(50, 170, 230);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    
    // Water surface highlights (sun reflection ripples)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Horizontal ripple lines
    glLineWidth(1);
    glBegin(GL_LINES);
    for (float y = 0.3f; y > -0.8f; y -= 0.15f) {
        for (float x = -0.9f; x < 0.9f; x += 0.25f) {
            glColor4ub(180, 220, 255, 80);
            glVertex2f(x, y);
            glColor4ub(220, 240, 255, 40);
            glVertex2f(x + 0.15f, y + 0.01f);
        }
    }
    glEnd();
    
    // Shimmer highlights
    glPointSize(2);
    glBegin(GL_POINTS);
    for (float y = 0.2f; y > -0.7f; y -= 0.2f) {
        for (float x = -0.8f; x < 0.8f; x += 0.3f) {
            glColor4ub(255, 255, 255, 60);
            glVertex2f(x + 0.05f * sin(y * 10), y);
        }
    }
    glEnd();
    
    glDisable(GL_BLEND);
}
void hut()
{
    // === MAIN HOUSE STRUCTURE ===
    // Front wall with gradient effect
    glBegin(GL_POLYGON);
    glColor3ub(194, 140, 70);  // Warm wood color
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.1f, 0.2f);
    glColor3ub(174, 120, 50);
    glVertex2f(-0.13f, -0.2f);
    glVertex2f(-0.49f, -0.2f);
    glEnd();
    
    // Front wall texture lines (horizontal planks)
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(140, 90, 30);
    for (float y = 0.15f; y >= -0.15f; y -= 0.07f) {
        glVertex2f(-0.48f, y);
        glVertex2f(-0.14f, y);
    }
    glEnd();
    
    // Roof - main slope with shingles effect
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);  // Saddle brown roof
    glVertex2f(-0.52f, 0.22f);
    glVertex2f(-0.08f, 0.22f);
    glVertex2f(-0.16f, 0.52f);
    glVertex2f(-0.6f, 0.52f);
    glEnd();
    
    // Roof shingle details
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(100, 50, 10);
    for (float y = 0.27f; y <= 0.47f; y += 0.05f) {
        float xLeft = -0.52f + (y - 0.22f) * 0.27f;
        float xRight = -0.08f - (y - 0.22f) * 0.27f;
        glVertex2f(xLeft, y);
        glVertex2f(xRight, y);
    }
    glEnd();
    
    // Roof edge highlight
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(89, 45, 10);
    glVertex2f(-0.52f, 0.22f);
    glVertex2f(-0.08f, 0.22f);
    glEnd();

    // Side wall (3D effect)
    glBegin(GL_POLYGON);
    glColor3ub(164, 110, 40);  // Darker side
    glVertex2f(-0.6f, 0.52f);
    glVertex2f(-0.65f, 0.2f);
    glVertex2f(-0.63f, 0.2f);
    glVertex2f(-0.63f, -0.15f);
    glVertex2f(-0.49f, -0.2f);
    glVertex2f(-0.49f, 0.2f);
    glEnd();
    
    // Side wall planks
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(120, 80, 25);
    for (float y = 0.15f; y >= -0.15f; y -= 0.07f) {
        glVertex2f(-0.62f, y + 0.02f);
        glVertex2f(-0.5f, y);
    }
    glEnd();

    // House outline
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(60, 40, 20);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.13f, -0.2f);
    glVertex2f(-0.49f, -0.2f);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(60, 40, 20);
    glVertex2f(-0.52f, 0.22f);
    glVertex2f(-0.6f, 0.52f);
    glVertex2f(-0.16f, 0.52f);
    glVertex2f(-0.08f, 0.22f);
    glEnd();

    // === MAIN DOOR (with frame and details) ===
    // Door frame
    glBegin(GL_POLYGON);
    glColor3ub(80, 50, 20);
    glVertex2f(-0.36f, 0.12f);
    glVertex2f(-0.21f, 0.12f);
    glVertex2f(-0.21f, -0.2f);
    glVertex2f(-0.36f, -0.2f);
    glEnd();
    
    // Door
    glBegin(GL_POLYGON);
    glColor3ub(120, 75, 30);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, -0.2f);
    glVertex2f(-0.35f, -0.2f);
    glEnd();
    
    // Door panels
    glBegin(GL_POLYGON);
    glColor3ub(100, 60, 25);
    glVertex2f(-0.34f, 0.08f);
    glVertex2f(-0.29f, 0.08f);
    glVertex2f(-0.29f, -0.02f);
    glVertex2f(-0.34f, -0.02f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(100, 60, 25);
    glVertex2f(-0.28f, 0.08f);
    glVertex2f(-0.23f, 0.08f);
    glVertex2f(-0.23f, -0.02f);
    glVertex2f(-0.28f, -0.02f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(100, 60, 25);
    glVertex2f(-0.34f, -0.05f);
    glVertex2f(-0.29f, -0.05f);
    glVertex2f(-0.29f, -0.17f);
    glVertex2f(-0.34f, -0.17f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(100, 60, 25);
    glVertex2f(-0.28f, -0.05f);
    glVertex2f(-0.23f, -0.05f);
    glVertex2f(-0.23f, -0.17f);
    glVertex2f(-0.28f, -0.17f);
    glEnd();
    
    // Door handle
    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3ub(200, 170, 50);  // Gold handle
    glVertex2f(-0.24f, -0.05f);
    glEnd();
    
    // Door outline
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(50, 30, 10);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, -0.2f);
    glVertex2f(-0.35f, -0.2f);
    glEnd();

    // === LEFT WINDOW (with frame and curtains) ===
    // Window frame
    glBegin(GL_POLYGON);
    glColor3ub(80, 50, 20);
    glVertex2f(-0.45f, 0.07f);
    glVertex2f(-0.37f, 0.07f);
    glVertex2f(-0.37f, -0.07f);
    glVertex2f(-0.45f, -0.07f);
    glEnd();
    
    // Window glass
    glBegin(GL_POLYGON);
    glColor3ub(180, 220, 255);  // Light blue glass
    glVertex2f(-0.44f, 0.05f);
    glVertex2f(-0.38f, 0.05f);
    glVertex2f(-0.38f, -0.05f);
    glVertex2f(-0.44f, -0.05f);
    glEnd();
    
    // Window cross
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(80, 50, 20);
    glVertex2f(-0.41f, 0.05f);
    glVertex2f(-0.41f, -0.05f);
    glVertex2f(-0.44f, 0.0f);
    glVertex2f(-0.38f, 0.0f);
    glEnd();
    
    // Window outline
    glBegin(GL_LINE_LOOP);
    glColor3ub(50, 30, 10);
    glVertex2f(-0.44f, 0.05f);
    glVertex2f(-0.38f, 0.05f);
    glVertex2f(-0.38f, -0.05f);
    glVertex2f(-0.44f, -0.05f);
    glEnd();

    // === RIGHT WINDOW ===
    glBegin(GL_POLYGON);
    glColor3ub(80, 50, 20);
    glVertex2f(-0.21f, 0.07f);
    glVertex2f(-0.13f, 0.07f);
    glVertex2f(-0.13f, -0.07f);
    glVertex2f(-0.21f, -0.07f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(180, 220, 255);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(-0.14f, -0.05f);
    glVertex2f(-0.2f, -0.05f);
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(80, 50, 20);
    glVertex2f(-0.17f, 0.05f);
    glVertex2f(-0.17f, -0.05f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(-0.14f, 0.0f);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3ub(50, 30, 10);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(-0.14f, -0.05f);
    glVertex2f(-0.2f, -0.05f);
    glEnd();

    // === SIDE DOOR ===
    glBegin(GL_POLYGON);
    glColor3ub(100, 65, 25);
    glVertex2f(-0.51f, 0.1f);
    glVertex2f(-0.58f, 0.12f);
    glVertex2f(-0.58f, -0.17f);
    glVertex2f(-0.51f, -0.2f);
    glEnd();
    
    // Side door panels
    glBegin(GL_POLYGON);
    glColor3ub(85, 55, 20);
    glVertex2f(-0.52f, 0.07f);
    glVertex2f(-0.57f, 0.09f);
    glVertex2f(-0.57f, -0.14f);
    glVertex2f(-0.52f, -0.17f);
    glEnd();
    
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(50, 30, 10);
    glVertex2f(-0.51f, 0.1f);
    glVertex2f(-0.58f, 0.12f);
    glVertex2f(-0.58f, -0.17f);
    glVertex2f(-0.51f, -0.2f);
    glEnd();
    
    // === CHIMNEY ===
    glBegin(GL_POLYGON);
    glColor3ub(150, 75, 40);
    glVertex2f(-0.48f, 0.42f);
    glVertex2f(-0.42f, 0.42f);
    glVertex2f(-0.42f, 0.58f);
    glVertex2f(-0.48f, 0.58f);
    glEnd();
    
    // Chimney top
    glBegin(GL_POLYGON);
    glColor3ub(120, 60, 30);
    glVertex2f(-0.49f, 0.58f);
    glVertex2f(-0.41f, 0.58f);
    glVertex2f(-0.41f, 0.6f);
    glVertex2f(-0.49f, 0.6f);
    glEnd();
    
    // Chimney bricks
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(100, 50, 25);
    glVertex2f(-0.48f, 0.48f);
    glVertex2f(-0.42f, 0.48f);
    glVertex2f(-0.48f, 0.54f);
    glVertex2f(-0.42f, 0.54f);
    glVertex2f(-0.45f, 0.42f);
    glVertex2f(-0.45f, 0.48f);
    glVertex2f(-0.45f, 0.54f);
    glVertex2f(-0.45f, 0.58f);
    glEnd();
    
    // Smoke from chimney
    int i;
    int triangleAmount = 12;
    GLfloat twicePi = 2.0f * PI;
    
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(200, 200, 200, 150);
    glVertex2f(-0.45f, 0.65f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(-0.45f + 0.02f * cos(i * twicePi / triangleAmount),
                   0.65f + 0.015f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glColor4ub(180, 180, 180, 120);
    glVertex2f(-0.47f, 0.7f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(-0.47f + 0.025f * cos(i * twicePi / triangleAmount),
                   0.7f + 0.018f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
}
void hut1()
{
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, -0.2f);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.35f, -0.2f);
    glVertex2f(-0.285f, 0.1f);
    glVertex2f(-0.285f, -0.2f);
    glEnd();

    /* glBegin(GL_POLYGON);
     glColor3ub(153, 115, 0);
      glVertex2f(-0.51f,0.12f); //left door
     glVertex2f(-0.58f,0.14f);
     glVertex2f(-0.58f,-0.17f);
     glVertex2f(-0.51f,-0.2f);
     glEnd();*/
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, 0.1f);
    glVertex2f(-0.22f, -0.2f);
    glVertex2f(-0.35f, 0.1f);
    glVertex2f(-0.35f, -0.2f);
    glVertex2f(-0.285f, 0.1f);
    glVertex2f(-0.285f, -0.2f);
    glEnd();

    /*glBegin(GL_POLYGON);
    glColor3ub(153, 115, 0);
    glVertex2f(-0.44f,0.05f);
    glVertex2f(-0.38f,0.05f); //left window
    glVertex2f(-0.38f,-0.05f);
    glVertex2f(-0.44f,-0.05f);
    glEnd();*/

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.44f, 0.05f);
    glVertex2f(-0.44f, -0.05f);
    glVertex2f(-0.38f, 0.05f);
    glVertex2f(-0.38f, -0.05f);
    glVertex2f(-0.44f, 0.05f);
    glVertex2f(-0.38f, 0.05f);
    glVertex2f(-0.44f, -0.05f);
    glVertex2f(-0.38f, -0.05f);
    glVertex2f(-0.41f, 0.05f);
    glVertex2f(-0.41f, -0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.58f, 0.14f);
    glVertex2f(-0.58f, -0.17f);
    glVertex2f(-0.51f, 0.12f);
    glVertex2f(-0.51f, -0.2f);
    glVertex2f(-0.58f, 0.14f);
    glVertex2f(-0.51f, 0.12f);
    glVertex2f(-0.545f, 0.13f);
    glVertex2f(-0.545f, -0.185f);
    glEnd();

    /*glBegin(GL_POLYGON);
   glColor3ub(153, 115, 0);
   glVertex2f(-0.14f,0.05f); ///right window
   glVertex2f(-0.2f,0.05f);
   glVertex2f(-0.2f,-0.05f);
   glVertex2f(-0.14f,-0.05f);
   glEnd();*/

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(-0.14f, -0.05f);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.2f, -0.05f);
    glVertex2f(-0.14f, 0.05f);
    glVertex2f(-0.2f, 0.05f);
    glVertex2f(-0.14f, -0.05f);
    glVertex2f(-0.2f, -0.05f);
    glVertex2f(-0.17f, 0.05f);
    glVertex2f(-0.17f, -0.05f);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.49f, 0.2f);
    glVertex2f(-0.49f, -0.2f);
    glVertex2f(-0.13f, -0.2f);
    glVertex2f(-0.49f, -0.2f);
    glVertex2f(-0.13f, -0.2f);
    glVertex2f(-0.13f, 0.2f);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.58f, 0.5f);
    glVertex2f(-0.58f, 0.5f);
    glVertex2f(-0.63f, 0.2f);
    glVertex2f(-0.57f, 0.445f);
    glVertex2f(-0.61f, 0.2f);
    glVertex2f(-0.61f, 0.2f);
    glVertex2f(-0.61f, -0.15f);
    glVertex2f(-0.61f, -0.15f);
    glVertex2f(-0.49f, -0.2f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.18f, 0.5f);
    glVertex2f(-0.18f, 0.5f);
    glVertex2f(-0.58f, 0.5f);

    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(204, 153, 0);
    glVertex2f(-0.5f, 0.2f);
    glVertex2f(-0.1f, 0.2f);
    glVertex2f(-0.18f, 0.5f);
    glVertex2f(-0.58f, 0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 153, 0);
    glVertex2f(-0.49f, 0.2f);
    glVertex2f(-0.13f, 0.2f);
    glVertex2f(-0.13f, -0.2f);
    glVertex2f(-0.49f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 153, 0);
    glVertex2f(-0.58f, 0.5f);
    glVertex2f(-0.63f, 0.2f);
    glVertex2f(-0.61f, 0.2f);
    glVertex2f(-0.61f, -0.15f);
    glVertex2f(-0.49f, -0.2f);
    glVertex2f(-0.17f, -0.2f);
    glEnd();
}

void tree()
{
    int i;
    int triangleAmount = 24;
    GLfloat twicePi = 2.0f * PI;
    
    // === TREE ROOTS (visible above ground) ===
    glBegin(GL_POLYGON);
    glColor3ub(80, 40, 10);
    glVertex2f(-0.72f, -0.15f);
    glVertex2f(-0.65f, -0.22f);
    glVertex2f(-0.70f, -0.18f);
    glVertex2f(-0.74f, -0.26f);
    glVertex2f(-0.75f, -0.18f);
    glVertex2f(-0.80f, -0.24f);
    glVertex2f(-0.78f, -0.15f);
    glEnd();
    
    // Root details
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(60, 30, 5);
    glVertex2f(-0.73f, -0.16f);
    glVertex2f(-0.68f, -0.20f);
    glVertex2f(-0.77f, -0.16f);
    glVertex2f(-0.82f, -0.21f);
    glEnd();

    // === MAIN TRUNK with bark texture ===
    // Trunk base (wider at bottom)
    glBegin(GL_POLYGON);
    glColor3ub(101, 67, 33);  // Dark brown bark
    glVertex2f(-0.79f, -0.15f);
    glVertex2f(-0.71f, -0.15f);
    glVertex2f(-0.72f, 0.23f);
    glVertex2f(-0.78f, 0.23f);
    glEnd();
    
    // Trunk highlight (left side light)
    glBegin(GL_POLYGON);
    glColor3ub(120, 85, 50);
    glVertex2f(-0.79f, -0.15f);
    glVertex2f(-0.76f, -0.15f);
    glVertex2f(-0.76f, 0.23f);
    glVertex2f(-0.78f, 0.23f);
    glEnd();
    
    // Bark texture lines
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(70, 45, 20);
    // Vertical bark lines
    glVertex2f(-0.74f, -0.12f);
    glVertex2f(-0.74f, 0.20f);
    glVertex2f(-0.76f, -0.10f);
    glVertex2f(-0.76f, 0.18f);
    // Horizontal bark marks
    glVertex2f(-0.78f, 0.0f);
    glVertex2f(-0.72f, 0.02f);
    glVertex2f(-0.78f, 0.1f);
    glVertex2f(-0.72f, 0.08f);
    glVertex2f(-0.77f, -0.08f);
    glVertex2f(-0.73f, -0.06f);
    glEnd();
    
    // Knot hole on trunk
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(50, 30, 15);
    glVertex2f(-0.745f, 0.05f);
    for (i = 0; i <= 12; i++) {
        glVertex2f(-0.745f + 0.012f * cos(i * twicePi / 12),
                   0.05f + 0.018f * sin(i * twicePi / 12));
    }
    glEnd();
    
    // === BRANCHES ===
    // Main upward branch
    glBegin(GL_POLYGON);
    glColor3ub(95, 60, 30);
    glVertex2f(-0.76f, 0.23f);
    glVertex2f(-0.74f, 0.23f);
    glVertex2f(-0.74f, 0.32f);
    glVertex2f(-0.76f, 0.32f);
    glEnd();
    
    // Left branch
    glBegin(GL_POLYGON);
    glColor3ub(90, 55, 28);
    glVertex2f(-0.78f, 0.20f);
    glVertex2f(-0.76f, 0.22f);
    glVertex2f(-0.84f, 0.30f);
    glVertex2f(-0.86f, 0.28f);
    glEnd();
    
    // Right branch
    glBegin(GL_POLYGON);
    glColor3ub(90, 55, 28);
    glVertex2f(-0.72f, 0.22f);
    glVertex2f(-0.74f, 0.20f);
    glVertex2f(-0.66f, 0.28f);
    glVertex2f(-0.64f, 0.30f);
    glEnd();
    
    // Small branches
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(85, 50, 25);
    glVertex2f(-0.84f, 0.29f);
    glVertex2f(-0.90f, 0.35f);
    glVertex2f(-0.65f, 0.29f);
    glVertex2f(-0.58f, 0.34f);
    glVertex2f(-0.75f, 0.32f);
    glVertex2f(-0.75f, 0.38f);
    glEnd();
    
    // === FOLIAGE - Multiple layers for depth ===
    // Background layer (darker green)
    float foliagePositions1[][2] = {
        {-0.92f, 0.38f}, {-0.58f, 0.38f}, {-0.75f, 0.55f}
    };
    for (int j = 0; j < 3; j++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(34, 139, 34);  // Forest green
        glVertex2f(foliagePositions1[j][0], foliagePositions1[j][1]);
        for (i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            float r = 0.07f + 0.015f * sin(angle * 5);  // Irregular edge
            glVertex2f(foliagePositions1[j][0] + r * cos(angle),
                      foliagePositions1[j][1] + r * sin(angle));
        }
        glEnd();
    }
    
    // Middle layer (medium green)
    float foliagePositions2[][2] = {
        {-0.75f, 0.35f}, {-0.68f, 0.33f}, {-0.82f, 0.33f},
        {-0.88f, 0.42f}, {-0.62f, 0.42f}
    };
    for (int j = 0; j < 5; j++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(50, 160, 50);
        glVertex2f(foliagePositions2[j][0], foliagePositions2[j][1]);
        for (i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            float r = 0.065f + 0.012f * sin(angle * 6);
            glVertex2f(foliagePositions2[j][0] + r * cos(angle),
                      foliagePositions2[j][1] + r * sin(angle));
        }
        glEnd();
    }
    
    // Front layer (lighter green with highlights)
    float foliagePositions3[][2] = {
        {-0.75f, 0.42f}, {-0.70f, 0.38f}, {-0.80f, 0.38f},
        {-0.85f, 0.46f}, {-0.65f, 0.46f}, {-0.75f, 0.50f}
    };
    for (int j = 0; j < 6; j++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(60, 180, 60);
        glVertex2f(foliagePositions3[j][0], foliagePositions3[j][1]);
        for (i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            float r = 0.055f + 0.01f * sin(angle * 4);
            glVertex2f(foliagePositions3[j][0] + r * cos(angle),
                      foliagePositions3[j][1] + r * sin(angle));
        }
        glEnd();
    }
    
    // Top highlights (lightest green)
    float highlightPositions[][2] = {
        {-0.73f, 0.48f}, {-0.78f, 0.44f}, {-0.68f, 0.40f}
    };
    for (int j = 0; j < 3; j++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(80, 200, 80);
        glVertex2f(highlightPositions[j][0], highlightPositions[j][1]);
        for (i = 0; i <= 16; i++) {
            float angle = i * twicePi / 16;
            glVertex2f(highlightPositions[j][0] + 0.03f * cos(angle),
                      highlightPositions[j][1] + 0.025f * sin(angle));
        }
        glEnd();
    }
    
    // === SHADOW at base ===
    glBegin(GL_POLYGON);
    glColor4ub(30, 30, 30, 100);
    glVertex2f(-0.82f, -0.2f);
    glVertex2f(-0.65f, -0.22f);
    glVertex2f(-0.60f, -0.24f);
    glVertex2f(-0.85f, -0.22f);
    glEnd();
}

void boat()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    
    // === WATER REFLECTION (below boat) ===
    glBegin(GL_POLYGON);
    glColor4ub(0, 50, 100, 80);
    glVertex2f(-0.22f, 0.33f);
    glVertex2f(-0.16f, 0.30f);
    glVertex2f(0.16f, 0.30f);
    glVertex2f(0.22f, 0.33f);
    glEnd();
    
    // === HULL - Bottom (underwater part) ===
    glBegin(GL_POLYGON);
    glColor3ub(60, 30, 15);  // Dark wood
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(-0.15f, 0.33f);
    glVertex2f(0.15f, 0.33f);
    glVertex2f(0.2f, 0.4f);
    glEnd();
    
    // Hull keel line
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(40, 20, 10);
    glVertex2f(-0.15f, 0.33f);
    glVertex2f(0.15f, 0.33f);
    glEnd();

    // === HULL - Main body ===
    // Outer hull (darker)
    glBegin(GL_POLYGON);
    glColor3ub(139, 90, 43);  // Sienna wood
    glVertex2f(-0.14f, 0.4f);
    glVertex2f(-0.12f, 0.48f);
    glVertex2f(-0.10f, 0.52f);
    glVertex2f(0.12f, 0.52f);
    glVertex2f(0.13f, 0.48f);
    glVertex2f(0.14f, 0.4f);
    glEnd();
    
    // Hull inner (lighter wood)
    glBegin(GL_POLYGON);
    glColor3ub(160, 110, 60);
    glVertex2f(-0.12f, 0.42f);
    glVertex2f(-0.10f, 0.47f);
    glVertex2f(-0.08f, 0.50f);
    glVertex2f(0.10f, 0.50f);
    glVertex2f(0.11f, 0.47f);
    glVertex2f(0.12f, 0.42f);
    glEnd();
    
    // Hull planks (horizontal lines)
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(100, 60, 30);
    glVertex2f(-0.13f, 0.44f);
    glVertex2f(0.13f, 0.44f);
    glVertex2f(-0.12f, 0.48f);
    glVertex2f(0.12f, 0.48f);
    glEnd();
    
    // Hull rim (top edge)
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3ub(80, 50, 25);
    glVertex2f(-0.14f, 0.4f);
    glVertex2f(-0.12f, 0.48f);
    glVertex2f(-0.10f, 0.52f);
    glVertex2f(0.12f, 0.52f);
    glVertex2f(0.13f, 0.48f);
    glVertex2f(0.14f, 0.4f);
    glEnd();
    
    // === MAST ===
    // Mast pole
    glBegin(GL_POLYGON);
    glColor3ub(101, 67, 33);
    glVertex2f(-0.008f, 0.50f);
    glVertex2f(0.008f, 0.50f);
    glVertex2f(0.006f, 0.82f);
    glVertex2f(-0.006f, 0.82f);
    glEnd();
    
    // Mast highlight
    glBegin(GL_POLYGON);
    glColor3ub(130, 90, 50);
    glVertex2f(-0.008f, 0.50f);
    glVertex2f(-0.002f, 0.50f);
    glVertex2f(-0.002f, 0.82f);
    glVertex2f(-0.006f, 0.82f);
    glEnd();
    
    // Mast top ball
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(180, 140, 80);
    glVertex2f(0.0f, 0.83f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(0.0f + 0.012f * cos(i * twicePi / triangleAmount),
                   0.83f + 0.012f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // === SAIL ===
    // Main sail (triangular)
    glBegin(GL_POLYGON);
    glColor3ub(255, 250, 240);  // Off-white canvas
    glVertex2f(0.0f, 0.80f);     // Top of mast
    glVertex2f(-0.08f, 0.55f);   // Back bottom
    glVertex2f(0.0f, 0.55f);     // Front bottom
    glEnd();
    
    // Sail shadow/fold
    glBegin(GL_POLYGON);
    glColor3ub(230, 225, 215);
    glVertex2f(0.0f, 0.80f);
    glVertex2f(-0.06f, 0.60f);
    glVertex2f(-0.03f, 0.58f);
    glEnd();
    
    // Secondary sail
    glBegin(GL_POLYGON);
    glColor3ub(245, 240, 230);
    glVertex2f(0.0f, 0.78f);
    glVertex2f(0.07f, 0.56f);
    glVertex2f(0.0f, 0.56f);
    glEnd();
    
    // Sail seams
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(200, 195, 185);
    glVertex2f(-0.01f, 0.75f);
    glVertex2f(-0.05f, 0.58f);
    glVertex2f(-0.01f, 0.70f);
    glVertex2f(-0.06f, 0.56f);
    glVertex2f(0.01f, 0.73f);
    glVertex2f(0.05f, 0.58f);
    glEnd();
    
    // Sail ropes
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(120, 100, 70);
    // Rope from mast top to hull front
    glVertex2f(0.0f, 0.82f);
    glVertex2f(0.10f, 0.51f);
    // Rope from mast top to hull back
    glVertex2f(0.0f, 0.82f);
    glVertex2f(-0.09f, 0.51f);
    glEnd();
    
    // === FLAG at top ===
    glBegin(GL_TRIANGLES);
    glColor3ub(220, 50, 50);  // Red flag
    glVertex2f(0.0f, 0.83f);
    glVertex2f(0.04f, 0.86f);
    glVertex2f(0.0f, 0.88f);
    glEnd();
    
    // === SEATS/BENCHES inside boat ===
    glBegin(GL_POLYGON);
    glColor3ub(120, 75, 40);
    glVertex2f(-0.06f, 0.46f);
    glVertex2f(0.06f, 0.46f);
    glVertex2f(0.06f, 0.44f);
    glVertex2f(-0.06f, 0.44f);
    glEnd();
    
    // Back seat
    glBegin(GL_POLYGON);
    glColor3ub(110, 70, 35);
    glVertex2f(-0.08f, 0.50f);
    glVertex2f(-0.02f, 0.50f);
    glVertex2f(-0.02f, 0.48f);
    glVertex2f(-0.08f, 0.48f);
    glEnd();
    
    // === BOATMAN ===
    drawBoatman(-0.05f, 0.52f, 0.8f);  // Position boatman in the boat
}

// Draw a boatman (person) at position (x, y) with scale
void drawBoatman(float x, float y, float scale)
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    
    // === HEAD ===
    // Face
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(222, 184, 135);  // Skin tone
    glVertex2f(0.0f, 0.12f);
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(0.0f + 0.022f * cos(i * twicePi / triangleAmount),
                   0.12f + 0.025f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // Hair
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(40, 30, 20);  // Dark brown hair
    glVertex2f(0.0f, 0.14f);
    for (i = 0; i <= triangleAmount; i++) {
        float angle = i * twicePi / triangleAmount;
        if (sin(angle) > 0) {  // Only top half
            glVertex2f(0.0f + 0.024f * cos(angle),
                       0.14f + 0.018f * sin(angle));
        }
    }
    glEnd();
    
    // Hat (straw hat / conical hat)
    glBegin(GL_TRIANGLES);
    glColor3ub(210, 180, 140);  // Tan/straw color
    glVertex2f(-0.04f, 0.13f);
    glVertex2f(0.04f, 0.13f);
    glVertex2f(0.0f, 0.2f);
    glEnd();
    
    // Hat brim
    glBegin(GL_POLYGON);
    glColor3ub(190, 160, 120);
    glVertex2f(-0.05f, 0.13f);
    glVertex2f(0.05f, 0.13f);
    glVertex2f(0.045f, 0.12f);
    glVertex2f(-0.045f, 0.12f);
    glEnd();
    
    // Hat band
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(139, 90, 43);
    glVertex2f(-0.03f, 0.145f);
    glVertex2f(0.03f, 0.145f);
    glEnd();
    
    // Eyes
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3ub(40, 30, 20);
    glVertex2f(-0.008f, 0.12f);
    glVertex2f(0.008f, 0.12f);
    glEnd();
    
    // Eyebrows
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(60, 45, 30);
    glVertex2f(-0.012f, 0.13f);
    glVertex2f(-0.004f, 0.132f);
    glVertex2f(0.004f, 0.132f);
    glVertex2f(0.012f, 0.13f);
    glEnd();
    
    // Nose
    glBegin(GL_LINES);
    glColor3ub(200, 160, 120);
    glVertex2f(0.0f, 0.115f);
    glVertex2f(0.0f, 0.105f);
    glEnd();
    
    // Mouth (smile)
    glBegin(GL_LINE_STRIP);
    glColor3ub(180, 100, 80);
    glVertex2f(-0.008f, 0.095f);
    glVertex2f(0.0f, 0.092f);
    glVertex2f(0.008f, 0.095f);
    glEnd();
    
    // === BODY / TORSO ===
    // Shirt
    glBegin(GL_POLYGON);
    glColor3ub(65, 105, 170);  // Blue shirt
    glVertex2f(-0.025f, 0.09f);
    glVertex2f(0.025f, 0.09f);
    glVertex2f(0.03f, 0.02f);
    glVertex2f(-0.03f, 0.02f);
    glEnd();
    
    // Shirt collar
    glBegin(GL_TRIANGLES);
    glColor3ub(55, 90, 150);
    glVertex2f(-0.01f, 0.09f);
    glVertex2f(0.01f, 0.09f);
    glVertex2f(0.0f, 0.08f);
    glEnd();
    
    // Shirt details (buttons)
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3ub(200, 200, 200);
    glVertex2f(0.0f, 0.07f);
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.0f, 0.03f);
    glEnd();
    
    // === ARMS ===
    // Left arm (holding oar)
    glBegin(GL_POLYGON);
    glColor3ub(222, 184, 135);  // Skin
    glVertex2f(-0.025f, 0.08f);
    glVertex2f(-0.035f, 0.08f);
    glVertex2f(-0.06f, 0.04f);
    glVertex2f(-0.05f, 0.03f);
    glEnd();
    
    // Left sleeve
    glBegin(GL_POLYGON);
    glColor3ub(55, 95, 160);
    glVertex2f(-0.025f, 0.085f);
    glVertex2f(-0.035f, 0.085f);
    glVertex2f(-0.045f, 0.06f);
    glVertex2f(-0.035f, 0.055f);
    glEnd();
    
    // Right arm (holding oar)
    glBegin(GL_POLYGON);
    glColor3ub(222, 184, 135);  // Skin
    glVertex2f(0.025f, 0.08f);
    glVertex2f(0.035f, 0.08f);
    glVertex2f(0.06f, 0.04f);
    glVertex2f(0.05f, 0.03f);
    glEnd();
    
    // Right sleeve
    glBegin(GL_POLYGON);
    glColor3ub(55, 95, 160);
    glVertex2f(0.025f, 0.085f);
    glVertex2f(0.035f, 0.085f);
    glVertex2f(0.045f, 0.06f);
    glVertex2f(0.035f, 0.055f);
    glEnd();
    
    // Hands
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(222, 184, 135);
    glVertex2f(-0.055f, 0.035f);
    for (i = 0; i <= 10; i++) {
        glVertex2f(-0.055f + 0.012f * cos(i * twicePi / 10),
                   0.035f + 0.01f * sin(i * twicePi / 10));
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(222, 184, 135);
    glVertex2f(0.055f, 0.035f);
    for (i = 0; i <= 10; i++) {
        glVertex2f(0.055f + 0.012f * cos(i * twicePi / 10),
                   0.035f + 0.01f * sin(i * twicePi / 10));
    }
    glEnd();
    
    // === OAR/PADDLE ===
    // Oar handle
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(139, 90, 43);  // Wood brown
    glVertex2f(-0.055f, 0.035f);
    glVertex2f(0.055f, 0.035f);
    glEnd();
    
    // Oar shaft (going into water)
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(120, 75, 35);
    glVertex2f(0.055f, 0.035f);
    glVertex2f(0.12f, -0.05f);
    glEnd();
    
    // Oar blade
    glBegin(GL_POLYGON);
    glColor3ub(160, 110, 60);
    glVertex2f(0.115f, -0.04f);
    glVertex2f(0.125f, -0.05f);
    glVertex2f(0.14f, -0.09f);
    glVertex2f(0.13f, -0.1f);
    glVertex2f(0.11f, -0.06f);
    glEnd();
    
    // === LEGS (sitting position) ===
    // Pants/lower body
    glBegin(GL_POLYGON);
    glColor3ub(100, 80, 60);  // Brown pants
    glVertex2f(-0.03f, 0.02f);
    glVertex2f(0.03f, 0.02f);
    glVertex2f(0.04f, -0.02f);
    glVertex2f(-0.04f, -0.02f);
    glEnd();
    
    // Left leg (bent, sitting)
    glBegin(GL_POLYGON);
    glColor3ub(90, 70, 50);
    glVertex2f(-0.03f, -0.01f);
    glVertex2f(-0.01f, -0.01f);
    glVertex2f(0.0f, -0.04f);
    glVertex2f(-0.04f, -0.04f);
    glEnd();
    
    // Right leg (bent, sitting)
    glBegin(GL_POLYGON);
    glColor3ub(90, 70, 50);
    glVertex2f(0.01f, -0.01f);
    glVertex2f(0.03f, -0.01f);
    glVertex2f(0.04f, -0.04f);
    glVertex2f(0.0f, -0.04f);
    glEnd();
    
    // Feet
    glBegin(GL_POLYGON);
    glColor3ub(50, 35, 20);  // Dark shoes
    glVertex2f(-0.04f, -0.035f);
    glVertex2f(-0.02f, -0.035f);
    glVertex2f(-0.015f, -0.05f);
    glVertex2f(-0.045f, -0.05f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(50, 35, 20);
    glVertex2f(0.02f, -0.035f);
    glVertex2f(0.04f, -0.035f);
    glVertex2f(0.045f, -0.05f);
    glVertex2f(0.015f, -0.05f);
    glEnd();
    
    glPopMatrix();
}

void boat2()
{
    // === ROWBOAT - Realistic wooden rowboat ===
    
    // Water reflection
    glBegin(GL_POLYGON);
    glColor4ub(20, 60, 90, 60);
    glVertex2f(0.40f, -0.62f);
    glVertex2f(0.50f, -0.65f);
    glVertex2f(0.80f, -0.65f);
    glVertex2f(0.90f, -0.52f);
    glEnd();
    
    // Hull bottom (underwater shadow)
    glBegin(GL_POLYGON);
    glColor3ub(50, 30, 15);
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.53f, -0.6f);
    glVertex2f(0.78f, -0.6f);
    glVertex2f(0.88f, -0.5f);
    glEnd();
    
    // Main hull body
    glBegin(GL_POLYGON);
    glColor3ub(139, 90, 43);  // Wood brown
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.53f, -0.53f);
    glVertex2f(0.63f, -0.53f);
    glVertex2f(0.73f, -0.53f);
    glVertex2f(0.78f, -0.53f);
    glVertex2f(0.88f, -0.5f);
    glVertex2f(0.80f, -0.46f);
    glVertex2f(0.73f, -0.45f);
    glVertex2f(0.63f, -0.45f);
    glVertex2f(0.53f, -0.45f);
    glVertex2f(0.45f, -0.47f);
    glEnd();
    
    // Hull inner (lighter)
    glBegin(GL_POLYGON);
    glColor3ub(170, 120, 70);
    glVertex2f(0.47f, -0.48f);
    glVertex2f(0.55f, -0.51f);
    glVertex2f(0.65f, -0.51f);
    glVertex2f(0.75f, -0.51f);
    glVertex2f(0.85f, -0.49f);
    glVertex2f(0.78f, -0.47f);
    glVertex2f(0.65f, -0.46f);
    glVertex2f(0.52f, -0.47f);
    glEnd();
    
    // Hull rim (top edge)
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3ub(100, 60, 30);
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.45f, -0.47f);
    glVertex2f(0.53f, -0.45f);
    glVertex2f(0.63f, -0.45f);
    glVertex2f(0.73f, -0.45f);
    glVertex2f(0.80f, -0.46f);
    glVertex2f(0.88f, -0.5f);
    glEnd();
    
    // Hull planks (ribs)
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(110, 70, 35);
    glVertex2f(0.53f, -0.45f);
    glVertex2f(0.53f, -0.53f);
    glVertex2f(0.63f, -0.45f);
    glVertex2f(0.63f, -0.53f);
    glVertex2f(0.73f, -0.45f);
    glVertex2f(0.73f, -0.53f);
    glEnd();
    
    // Seats inside boat
    glBegin(GL_POLYGON);
    glColor3ub(120, 75, 40);
    glVertex2f(0.55f, -0.47f);
    glVertex2f(0.60f, -0.47f);
    glVertex2f(0.60f, -0.49f);
    glVertex2f(0.55f, -0.49f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3ub(115, 70, 38);
    glVertex2f(0.68f, -0.47f);
    glVertex2f(0.75f, -0.47f);
    glVertex2f(0.75f, -0.49f);
    glVertex2f(0.68f, -0.49f);
    glEnd();
    
    // === FISHING POLE ===
    // Pole
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(139, 90, 43);
    glVertex2f(0.40f, -0.35f);
    glVertex2f(0.45f, -0.5f);
    glEnd();
    
    // Pole tip (thinner)
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(160, 110, 60);
    glVertex2f(0.38f, -0.28f);
    glVertex2f(0.40f, -0.35f);
    glEnd();
    
    // Fishing line
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(200, 200, 200);
    glVertex2f(0.38f, -0.28f);
    glVertex2f(0.35f, -0.55f);
    glEnd();
    
    // Bobber
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 50, 50);
    int triangleAmount = 12;
    GLfloat twicePi = 2.0f * PI;
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(0.35f + 0.015f * cos(i * twicePi / triangleAmount),
                   -0.55f + 0.015f * sin(i * twicePi / triangleAmount));
    }
    glEnd();
    
    // Anchor rope coiled in boat
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glColor3ub(150, 130, 90);
    glVertex2f(0.82f, -0.48f);
    glVertex2f(0.84f, -0.50f);
    glVertex2f(0.82f, -0.52f);
    glVertex2f(0.84f, -0.54f);
    glEnd();
    
    // === FISHERMAN (sitting in rowboat) ===
    drawBoatman(0.62f, -0.43f, 0.6f);  // Smaller boatman for the rowboat
}
void boat3()
{
    // boat3 - Simplified version, uses same style as boat2
    // This function draws a stationary boat similar to boat2
    // Keeping minimal for night scene visibility
    
    // Hull shadow
    glBegin(GL_POLYGON);
    glColor3ub(50, 30, 15);
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.53f, -0.6f);
    glVertex2f(0.78f, -0.6f);
    glVertex2f(0.88f, -0.5f);
    glEnd();
    
    // Main hull
    glBegin(GL_POLYGON);
    glColor3ub(120, 80, 40);
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.53f, -0.53f);
    glVertex2f(0.78f, -0.53f);
    glVertex2f(0.88f, -0.5f);
    glVertex2f(0.80f, -0.46f);
    glVertex2f(0.53f, -0.46f);
    glEnd();
    
    // Hull inner
    glBegin(GL_POLYGON);
    glColor3ub(150, 105, 55);
    glVertex2f(0.47f, -0.49f);
    glVertex2f(0.55f, -0.51f);
    glVertex2f(0.75f, -0.51f);
    glVertex2f(0.84f, -0.49f);
    glVertex2f(0.78f, -0.47f);
    glVertex2f(0.55f, -0.47f);
    glEnd();
    
    // Hull rim
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glColor3ub(90, 55, 28);
    glVertex2f(0.43f, -0.5f);
    glVertex2f(0.53f, -0.46f);
    glVertex2f(0.80f, -0.46f);
    glVertex2f(0.88f, -0.5f);
    glEnd();
    
    // Ribs
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(100, 65, 32);
    glVertex2f(0.58f, -0.46f);
    glVertex2f(0.58f, -0.52f);
    glVertex2f(0.68f, -0.46f);
    glVertex2f(0.68f, -0.52f);
    glEnd();
}

void boat4()
{
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0.3f, -0.25f);
    glVertex2f(0.35f, -0.3f);
    glVertex2f(0.65f, -0.3f);
    glVertex2f(0.7f, -0.25f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 153, 0);
    glVertex2f(0.37f, -0.25f);
    glVertex2f(0.39f, -0.17f);
    glVertex2f(0.412f, -0.13f);
    glVertex2f(0.63f, -0.13f);
    glVertex2f(0.64f, -0.16f);
    glVertex2f(0.65f, -0.25f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 25, 25);
    glVertex2f(0.462f, -0.08f);
    glVertex2f(0.462f, 0.08f);
    glVertex2f(0.465f, 0.1f);
    glVertex2f(0.564f, 0.08f);
    glVertex2f(0.565f, 0.06f);
    glVertex2f(0.565f, -0.1f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(136, 204, 0);
    glVertex2f(0.5f, -0.13f);
    glVertex2f(0.5f, 0.14f);
    glVertex2f(0.51f, 0.14f);
    glVertex2f(0.51f, -0.13f);
    glEnd();
}
void Straw()
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 219, 77);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.07f, 0.15f);
    glVertex2f(0.02f, 0.22f);
    glVertex2f(-0.05f, 0.27f);
    glVertex2f(-0.12f, 0.22f);
    glVertex2f(-0.17f, 0.15f);
    glVertex2f(-0.2f, 0.1f);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(153, 153, 102);
    glVertex2f(-0.05f, 0.27f);
    glVertex2f(-0.05f, 0.31f);
    glEnd();
}
void way()
{
    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(-0.35f, -0.2f);
    glVertex2f(-0.22f, -0.2f);
    glVertex2f(-0.28f, -0.5f);
    glVertex2f(-0.43f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(153, 153, 102);
    glVertex2f(-0.43f, -0.5f);
    glVertex2f(-0.75f, -1.0f);
    glVertex2f(-0.56f, -1.0f);
    glVertex2f(-0.28f, -0.5f);
    glEnd();
}
void grass1()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = 0.0f;
    float baseY = -0.4f;
    
    // === GRASS BLADES (multiple layers for depth) ===
    // Back layer (darker)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(20, 80, 20);
    glVertex2f(baseX - 0.08f, baseY - 0.02f); glVertex2f(baseX - 0.04f, baseY + 0.08f);
    glVertex2f(baseX + 0.08f, baseY - 0.02f); glVertex2f(baseX + 0.05f, baseY + 0.07f);
    glVertex2f(baseX - 0.06f, baseY - 0.01f); glVertex2f(baseX - 0.08f, baseY + 0.06f);
    glVertex2f(baseX + 0.06f, baseY - 0.01f); glVertex2f(baseX + 0.08f, baseY + 0.05f);
    glEnd();
    
    // Middle layer
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(34, 120, 34);
    glVertex2f(baseX - 0.05f, baseY); glVertex2f(baseX - 0.02f, baseY + 0.1f);
    glVertex2f(baseX + 0.05f, baseY); glVertex2f(baseX + 0.02f, baseY + 0.1f);
    glVertex2f(baseX - 0.03f, baseY); glVertex2f(baseX - 0.05f, baseY + 0.09f);
    glVertex2f(baseX + 0.03f, baseY); glVertex2f(baseX + 0.05f, baseY + 0.08f);
    glEnd();
    
    // Front layer (brighter)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(50, 160, 50);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.12f);
    glVertex2f(baseX - 0.02f, baseY); glVertex2f(baseX - 0.03f, baseY + 0.08f);
    glVertex2f(baseX + 0.02f, baseY); glVertex2f(baseX + 0.03f, baseY + 0.07f);
    glEnd();
    
    // === FLOWER 1 (Red Rose-like) ===
    float f1x = baseX - 0.05f, f1y = baseY + 0.05f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(34, 100, 34);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    // Petals (layered)
    for (int layer = 0; layer < 3; layer++) {
        float petalR = 0.022f - layer * 0.005f;
        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(220 - layer * 30, 50 + layer * 20, 60);
        glVertex2f(f1x, f1y);
        for (i = 0; i <= 8; i++) {
            float angle = i * twicePi / 8 + layer * 0.3f;
            glVertex2f(f1x + petalR * cos(angle), f1y + petalR * 0.8f * sin(angle));
        }
        glEnd();
    }
    // Center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 220, 50);
    glVertex2f(f1x, f1y);
    for (i = 0; i <= 10; i++) {
        glVertex2f(f1x + 0.006f * cos(i * twicePi / 10), f1y + 0.006f * sin(i * twicePi / 10));
    }
    glEnd();
    
    // === FLOWER 2 (Orange Daisy) ===
    float f2x = baseX + 0.05f, f2y = baseY + 0.06f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(40, 110, 40);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    // Petals
    for (i = 0; i < 8; i++) {
        float angle = i * twicePi / 8;
        glBegin(GL_POLYGON);
        glColor3ub(255, 140, 30);
        glVertex2f(f2x, f2y);
        glVertex2f(f2x + 0.015f * cos(angle - 0.3f), f2y + 0.015f * sin(angle - 0.3f));
        glColor3ub(255, 180, 80);
        glVertex2f(f2x + 0.025f * cos(angle), f2y + 0.025f * sin(angle));
        glVertex2f(f2x + 0.015f * cos(angle + 0.3f), f2y + 0.015f * sin(angle + 0.3f));
        glEnd();
    }
    // Center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(80, 50, 20);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 12; i++) {
        glVertex2f(f2x + 0.01f * cos(i * twicePi / 12), f2y + 0.01f * sin(i * twicePi / 12));
    }
    glEnd();
    
    // === FLOWER 3 (Yellow Sunflower-like) ===
    float f3x = baseX, f3y = baseY + 0.1f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(45, 120, 45);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    // Leaf on stem
    glBegin(GL_TRIANGLES);
    glColor3ub(50, 140, 50);
    glVertex2f(f3x, baseY + 0.04f);
    glVertex2f(f3x - 0.025f, baseY + 0.05f);
    glVertex2f(f3x, baseY + 0.06f);
    glEnd();
    // Petals
    for (i = 0; i < 10; i++) {
        float angle = i * twicePi / 10;
        glBegin(GL_POLYGON);
        glColor3ub(255, 230, 50);
        glVertex2f(f3x + 0.008f * cos(angle), f3y + 0.008f * sin(angle));
        glColor3ub(255, 200, 0);
        glVertex2f(f3x + 0.022f * cos(angle - 0.15f), f3y + 0.022f * sin(angle - 0.15f));
        glVertex2f(f3x + 0.028f * cos(angle), f3y + 0.028f * sin(angle));
        glVertex2f(f3x + 0.022f * cos(angle + 0.15f), f3y + 0.022f * sin(angle + 0.15f));
        glEnd();
    }
    // Center with seeds pattern
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(90, 60, 20);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 16; i++) {
        glVertex2f(f3x + 0.012f * cos(i * twicePi / 16), f3y + 0.012f * sin(i * twicePi / 16));
    }
    glEnd();
    // Seed dots
    glPointSize(1.5f);
    glBegin(GL_POINTS);
    glColor3ub(60, 40, 15);
    for (i = 0; i < 6; i++) {
        float angle = i * twicePi / 6;
        glVertex2f(f3x + 0.006f * cos(angle), f3y + 0.006f * sin(angle));
    }
    glEnd();
}
void grass2()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = 0.0f;
    float baseY = -0.7f;
    
    // === GRASS BLADES (multiple layers for depth) ===
    // Back layer (darker)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(25, 85, 25);
    glVertex2f(baseX - 0.07f, baseY - 0.02f); glVertex2f(baseX - 0.03f, baseY + 0.09f);
    glVertex2f(baseX + 0.07f, baseY - 0.02f); glVertex2f(baseX + 0.04f, baseY + 0.08f);
    glVertex2f(baseX - 0.05f, baseY - 0.01f); glVertex2f(baseX - 0.07f, baseY + 0.07f);
    glVertex2f(baseX + 0.05f, baseY - 0.01f); glVertex2f(baseX + 0.07f, baseY + 0.06f);
    glEnd();
    
    // Middle layer
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(40, 130, 40);
    glVertex2f(baseX - 0.04f, baseY); glVertex2f(baseX - 0.01f, baseY + 0.11f);
    glVertex2f(baseX + 0.04f, baseY); glVertex2f(baseX + 0.01f, baseY + 0.11f);
    glVertex2f(baseX - 0.02f, baseY); glVertex2f(baseX - 0.04f, baseY + 0.1f);
    glVertex2f(baseX + 0.02f, baseY); glVertex2f(baseX + 0.04f, baseY + 0.09f);
    glEnd();
    
    // Front layer (brighter)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(55, 170, 55);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.13f);
    glVertex2f(baseX - 0.015f, baseY); glVertex2f(baseX - 0.025f, baseY + 0.09f);
    glVertex2f(baseX + 0.015f, baseY); glVertex2f(baseX + 0.025f, baseY + 0.08f);
    glEnd();
    
    // === FLOWER 1 (Pink Tulip) ===
    float f1x = baseX - 0.04f, f1y = baseY + 0.06f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(35, 105, 35);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    // Tulip petals
    glBegin(GL_POLYGON);
    glColor3ub(255, 150, 180);
    glVertex2f(f1x - 0.018f, f1y);
    glVertex2f(f1x - 0.01f, f1y + 0.03f);
    glColor3ub(255, 100, 140);
    glVertex2f(f1x, f1y + 0.035f);
    glVertex2f(f1x + 0.01f, f1y + 0.03f);
    glColor3ub(255, 150, 180);
    glVertex2f(f1x + 0.018f, f1y);
    glEnd();
    
    // === FLOWER 2 (Purple Violet) ===
    float f2x = baseX + 0.04f, f2y = baseY + 0.07f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(42, 115, 42);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    // Petals
    for (i = 0; i < 5; i++) {
        float angle = i * twicePi / 5 - PI/2;
        glBegin(GL_POLYGON);
        glColor3ub(150, 80, 200);
        glVertex2f(f2x, f2y);
        glColor3ub(200, 150, 255);
        glVertex2f(f2x + 0.018f * cos(angle - 0.3f), f2y + 0.018f * sin(angle - 0.3f));
        glVertex2f(f2x + 0.025f * cos(angle), f2y + 0.025f * sin(angle));
        glVertex2f(f2x + 0.018f * cos(angle + 0.3f), f2y + 0.018f * sin(angle + 0.3f));
        glEnd();
    }
    // Center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 255, 100);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f2x + 0.007f * cos(i * twicePi / 8), f2y + 0.007f * sin(i * twicePi / 8));
    }
    glEnd();
    
    // === FLOWER 3 (White Daisy) ===
    float f3x = baseX, f3y = baseY + 0.11f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(48, 125, 48);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    // Leaf
    glBegin(GL_TRIANGLES);
    glColor3ub(55, 145, 55);
    glVertex2f(f3x, baseY + 0.05f);
    glVertex2f(f3x + 0.022f, baseY + 0.06f);
    glVertex2f(f3x, baseY + 0.07f);
    glEnd();
    // White petals
    for (i = 0; i < 12; i++) {
        float angle = i * twicePi / 12;
        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);
        glVertex2f(f3x + 0.005f * cos(angle), f3y + 0.005f * sin(angle));
        glColor3ub(240, 240, 250);
        glVertex2f(f3x + 0.018f * cos(angle - 0.12f), f3y + 0.018f * sin(angle - 0.12f));
        glVertex2f(f3x + 0.023f * cos(angle), f3y + 0.023f * sin(angle));
        glVertex2f(f3x + 0.018f * cos(angle + 0.12f), f3y + 0.018f * sin(angle + 0.12f));
        glEnd();
    }
    // Yellow center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255, 220, 50);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 12; i++) {
        glVertex2f(f3x + 0.009f * cos(i * twicePi / 12), f3y + 0.009f * sin(i * twicePi / 12));
    }
    glEnd();
}
void grass3()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = -0.8f;
    float baseY = -0.8f;
    
    // === GRASS BLADES ===
    // Back layer
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(22, 78, 22);
    glVertex2f(baseX - 0.06f, baseY - 0.01f); glVertex2f(baseX - 0.02f, baseY + 0.1f);
    glVertex2f(baseX + 0.06f, baseY - 0.01f); glVertex2f(baseX + 0.03f, baseY + 0.09f);
    glVertex2f(baseX - 0.04f, baseY); glVertex2f(baseX - 0.06f, baseY + 0.08f);
    glVertex2f(baseX + 0.04f, baseY); glVertex2f(baseX + 0.06f, baseY + 0.07f);
    glEnd();
    
    // Middle layer
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(38, 125, 38);
    glVertex2f(baseX - 0.03f, baseY); glVertex2f(baseX - 0.01f, baseY + 0.12f);
    glVertex2f(baseX + 0.03f, baseY); glVertex2f(baseX + 0.01f, baseY + 0.11f);
    glVertex2f(baseX - 0.015f, baseY); glVertex2f(baseX - 0.03f, baseY + 0.1f);
    glVertex2f(baseX + 0.015f, baseY); glVertex2f(baseX + 0.03f, baseY + 0.09f);
    glEnd();
    
    // Front layer
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(52, 165, 52);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.14f);
    glVertex2f(baseX - 0.01f, baseY); glVertex2f(baseX - 0.02f, baseY + 0.09f);
    glVertex2f(baseX + 0.01f, baseY); glVertex2f(baseX + 0.02f, baseY + 0.08f);
    glEnd();
    
    // === FLOWER 1 (Red Poppy) ===
    float f1x = baseX - 0.035f, f1y = baseY + 0.07f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(36, 102, 36);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    // Petals (cup shape)
    for (i = 0; i < 6; i++) {
        float angle = i * twicePi / 6 + 0.2f;
        glBegin(GL_POLYGON);
        glColor3ub(230, 30, 30);
        glVertex2f(f1x, f1y);
        glColor3ub(180, 20, 20);
        glVertex2f(f1x + 0.016f * cos(angle - 0.25f), f1y + 0.016f * sin(angle - 0.25f));
        glVertex2f(f1x + 0.024f * cos(angle), f1y + 0.024f * sin(angle));
        glVertex2f(f1x + 0.016f * cos(angle + 0.25f), f1y + 0.016f * sin(angle + 0.25f));
        glEnd();
    }
    // Dark center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(30, 30, 30);
    glVertex2f(f1x, f1y);
    for (i = 0; i <= 10; i++) {
        glVertex2f(f1x + 0.008f * cos(i * twicePi / 10), f1y + 0.008f * sin(i * twicePi / 10));
    }
    glEnd();
    
    // === FLOWER 2 (Blue Cornflower) ===
    float f2x = baseX + 0.035f, f2y = baseY + 0.08f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(40, 108, 40);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    // Spiky petals
    for (i = 0; i < 14; i++) {
        float angle = i * twicePi / 14;
        float len = (i % 2 == 0) ? 0.022f : 0.016f;
        glBegin(GL_TRIANGLES);
        glColor3ub(80, 120, 220);
        glVertex2f(f2x + 0.005f * cos(angle - 0.2f), f2y + 0.005f * sin(angle - 0.2f));
        glColor3ub(100, 150, 255);
        glVertex2f(f2x + len * cos(angle), f2y + len * sin(angle));
        glColor3ub(80, 120, 220);
        glVertex2f(f2x + 0.005f * cos(angle + 0.2f), f2y + 0.005f * sin(angle + 0.2f));
        glEnd();
    }
    // Center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(180, 100, 180);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f2x + 0.006f * cos(i * twicePi / 8), f2y + 0.006f * sin(i * twicePi / 8));
    }
    glEnd();
    
    // === FLOWER 3 (Yellow Buttercup) ===
    float f3x = baseX, f3y = baseY + 0.12f;
    // Stem
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(45, 115, 45);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    // Shiny petals
    for (i = 0; i < 5; i++) {
        float angle = i * twicePi / 5 - PI/2;
        glBegin(GL_POLYGON);
        glColor3ub(255, 240, 50);
        glVertex2f(f3x, f3y);
        glColor3ub(255, 220, 0);
        glVertex2f(f3x + 0.014f * cos(angle - 0.28f), f3y + 0.014f * sin(angle - 0.28f));
        glColor3ub(255, 255, 150);
        glVertex2f(f3x + 0.02f * cos(angle), f3y + 0.02f * sin(angle));
        glColor3ub(255, 220, 0);
        glVertex2f(f3x + 0.014f * cos(angle + 0.28f), f3y + 0.014f * sin(angle + 0.28f));
        glEnd();
    }
    // Green center
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(150, 180, 50);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f3x + 0.005f * cos(i * twicePi / 8), f3y + 0.005f * sin(i * twicePi / 8));
    }
    glEnd();
}

void fence()
{
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 102);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(-0.6f, -0.1f);

    glColor3ub(255, 255, 102);
    glVertex2f(-1.0f, -0.05f);
    glVertex2f(-0.6f, -0.05f);

    glColor3ub(255, 255, 102);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(-0.6f, 0.0f);

    glColor3ub(255, 255, 102);
    glVertex2f(-1.0f, 0.05f);
    glVertex2f(-0.6f, 0.05f);

    glColor3ub(255, 255, 102);
    glVertex2f(-1.0f, 0.1f);
    glVertex2f(-0.6f, 0.1f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.95f, 0.13f);
    glVertex2f(-0.95f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.9f, 0.13f);
    glVertex2f(-0.9f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.85f, 0.13f);
    glVertex2f(-0.85f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.8f, 0.13f);
    glVertex2f(-0.8f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.75f, 0.13f);
    glVertex2f(-0.75f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.7f, 0.13f);
    glVertex2f(-0.7f, -0.12f);

    glColor3ub(255, 255, 102);
    glVertex2f(-0.65f, 0.13f);
    glVertex2f(-0.65f, -0.12f);

    glEnd();
}
void grass4()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = 0.0f;
    float baseY = -0.4f;
    
    // Night grass (darker shades)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(15, 50, 15);
    glVertex2f(baseX - 0.07f, baseY - 0.02f); glVertex2f(baseX - 0.03f, baseY + 0.08f);
    glVertex2f(baseX + 0.07f, baseY - 0.02f); glVertex2f(baseX + 0.04f, baseY + 0.07f);
    glVertex2f(baseX - 0.05f, baseY - 0.01f); glVertex2f(baseX - 0.07f, baseY + 0.06f);
    glVertex2f(baseX + 0.05f, baseY - 0.01f); glVertex2f(baseX + 0.07f, baseY + 0.05f);
    glEnd();
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(20, 70, 20);
    glVertex2f(baseX - 0.04f, baseY); glVertex2f(baseX - 0.01f, baseY + 0.1f);
    glVertex2f(baseX + 0.04f, baseY); glVertex2f(baseX + 0.01f, baseY + 0.1f);
    glVertex2f(baseX - 0.02f, baseY); glVertex2f(baseX - 0.04f, baseY + 0.09f);
    glVertex2f(baseX + 0.02f, baseY); glVertex2f(baseX + 0.04f, baseY + 0.08f);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(30, 90, 30);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.12f);
    glVertex2f(baseX - 0.015f, baseY); glVertex2f(baseX - 0.025f, baseY + 0.08f);
    glVertex2f(baseX + 0.015f, baseY); glVertex2f(baseX + 0.025f, baseY + 0.07f);
    glEnd();
    
    // Night flowers (muted colors with moonlight sheen)
    float f1x = baseX - 0.04f, f1y = baseY + 0.05f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(25, 60, 25);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    for (i = 0; i < 6; i++) {
        float angle = i * twicePi / 6;
        glBegin(GL_POLYGON);
        glColor3ub(140, 30, 40);
        glVertex2f(f1x, f1y);
        glColor3ub(100, 20, 30);
        glVertex2f(f1x + 0.016f * cos(angle - 0.25f), f1y + 0.016f * sin(angle - 0.25f));
        glVertex2f(f1x + 0.022f * cos(angle), f1y + 0.022f * sin(angle));
        glVertex2f(f1x + 0.016f * cos(angle + 0.25f), f1y + 0.016f * sin(angle + 0.25f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(180, 160, 80);
    glVertex2f(f1x, f1y);
    for (i = 0; i <= 10; i++) {
        glVertex2f(f1x + 0.006f * cos(i * twicePi / 10), f1y + 0.006f * sin(i * twicePi / 10));
    }
    glEnd();
    
    float f2x = baseX + 0.04f, f2y = baseY + 0.06f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(28, 65, 28);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    for (i = 0; i < 8; i++) {
        float angle = i * twicePi / 8;
        glBegin(GL_POLYGON);
        glColor3ub(180, 100, 20);
        glVertex2f(f2x, f2y);
        glColor3ub(140, 70, 10);
        glVertex2f(f2x + 0.014f * cos(angle - 0.3f), f2y + 0.014f * sin(angle - 0.3f));
        glVertex2f(f2x + 0.02f * cos(angle), f2y + 0.02f * sin(angle));
        glVertex2f(f2x + 0.014f * cos(angle + 0.3f), f2y + 0.014f * sin(angle + 0.3f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(60, 40, 20);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 10; i++) {
        glVertex2f(f2x + 0.008f * cos(i * twicePi / 10), f2y + 0.008f * sin(i * twicePi / 10));
    }
    glEnd();
    
    float f3x = baseX, f3y = baseY + 0.1f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(32, 72, 32);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    for (i = 0; i < 10; i++) {
        float angle = i * twicePi / 10;
        glBegin(GL_POLYGON);
        glColor3ub(180, 170, 40);
        glVertex2f(f3x + 0.006f * cos(angle), f3y + 0.006f * sin(angle));
        glColor3ub(150, 140, 20);
        glVertex2f(f3x + 0.018f * cos(angle - 0.15f), f3y + 0.018f * sin(angle - 0.15f));
        glVertex2f(f3x + 0.024f * cos(angle), f3y + 0.024f * sin(angle));
        glVertex2f(f3x + 0.018f * cos(angle + 0.15f), f3y + 0.018f * sin(angle + 0.15f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(70, 50, 20);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 12; i++) {
        glVertex2f(f3x + 0.01f * cos(i * twicePi / 12), f3y + 0.01f * sin(i * twicePi / 12));
    }
    glEnd();
}
void grass5()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = 0.0f;
    float baseY = -0.7f;
    
    // Night grass (darker)
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(18, 55, 18);
    glVertex2f(baseX - 0.06f, baseY - 0.02f); glVertex2f(baseX - 0.02f, baseY + 0.09f);
    glVertex2f(baseX + 0.06f, baseY - 0.02f); glVertex2f(baseX + 0.03f, baseY + 0.08f);
    glVertex2f(baseX - 0.04f, baseY - 0.01f); glVertex2f(baseX - 0.06f, baseY + 0.07f);
    glVertex2f(baseX + 0.04f, baseY - 0.01f); glVertex2f(baseX + 0.06f, baseY + 0.06f);
    glEnd();
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(25, 80, 25);
    glVertex2f(baseX - 0.03f, baseY); glVertex2f(baseX, baseY + 0.11f);
    glVertex2f(baseX + 0.03f, baseY); glVertex2f(baseX + 0.01f, baseY + 0.11f);
    glVertex2f(baseX - 0.015f, baseY); glVertex2f(baseX - 0.03f, baseY + 0.1f);
    glVertex2f(baseX + 0.015f, baseY); glVertex2f(baseX + 0.03f, baseY + 0.09f);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(35, 100, 35);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.13f);
    glVertex2f(baseX - 0.01f, baseY); glVertex2f(baseX - 0.02f, baseY + 0.09f);
    glVertex2f(baseX + 0.01f, baseY); glVertex2f(baseX + 0.02f, baseY + 0.08f);
    glEnd();
    
    // Night tulip
    float f1x = baseX - 0.035f, f1y = baseY + 0.06f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(22, 62, 22);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(180, 100, 130);
    glVertex2f(f1x - 0.016f, f1y);
    glVertex2f(f1x - 0.008f, f1y + 0.028f);
    glColor3ub(140, 70, 100);
    glVertex2f(f1x, f1y + 0.032f);
    glVertex2f(f1x + 0.008f, f1y + 0.028f);
    glColor3ub(180, 100, 130);
    glVertex2f(f1x + 0.016f, f1y);
    glEnd();
    
    // Night violet
    float f2x = baseX + 0.035f, f2y = baseY + 0.07f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(26, 68, 26);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    for (i = 0; i < 5; i++) {
        float angle = i * twicePi / 5 - PI/2;
        glBegin(GL_POLYGON);
        glColor3ub(100, 50, 140);
        glVertex2f(f2x, f2y);
        glColor3ub(140, 100, 180);
        glVertex2f(f2x + 0.016f * cos(angle - 0.28f), f2y + 0.016f * sin(angle - 0.28f));
        glVertex2f(f2x + 0.022f * cos(angle), f2y + 0.022f * sin(angle));
        glVertex2f(f2x + 0.016f * cos(angle + 0.28f), f2y + 0.016f * sin(angle + 0.28f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(180, 180, 80);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f2x + 0.006f * cos(i * twicePi / 8), f2y + 0.006f * sin(i * twicePi / 8));
    }
    glEnd();
    
    // Night daisy with moonlight
    float f3x = baseX, f3y = baseY + 0.11f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(30, 75, 30);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    for (i = 0; i < 12; i++) {
        float angle = i * twicePi / 12;
        glBegin(GL_POLYGON);
        glColor3ub(200, 200, 210);
        glVertex2f(f3x + 0.004f * cos(angle), f3y + 0.004f * sin(angle));
        glColor3ub(180, 180, 195);
        glVertex2f(f3x + 0.016f * cos(angle - 0.12f), f3y + 0.016f * sin(angle - 0.12f));
        glVertex2f(f3x + 0.02f * cos(angle), f3y + 0.02f * sin(angle));
        glVertex2f(f3x + 0.016f * cos(angle + 0.12f), f3y + 0.016f * sin(angle + 0.12f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(180, 160, 50);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 10; i++) {
        glVertex2f(f3x + 0.007f * cos(i * twicePi / 10), f3y + 0.007f * sin(i * twicePi / 10));
    }
    glEnd();
}
void grass6()
{
    int i;
    int triangleAmount = 16;
    GLfloat twicePi = 2.0f * PI;
    float baseX = -0.8f;
    float baseY = -0.8f;
    
    // Night grass
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(16, 52, 16);
    glVertex2f(baseX - 0.055f, baseY - 0.01f); glVertex2f(baseX - 0.015f, baseY + 0.1f);
    glVertex2f(baseX + 0.055f, baseY - 0.01f); glVertex2f(baseX + 0.025f, baseY + 0.09f);
    glVertex2f(baseX - 0.035f, baseY); glVertex2f(baseX - 0.055f, baseY + 0.08f);
    glVertex2f(baseX + 0.035f, baseY); glVertex2f(baseX + 0.055f, baseY + 0.07f);
    glEnd();
    
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(24, 75, 24);
    glVertex2f(baseX - 0.025f, baseY); glVertex2f(baseX - 0.005f, baseY + 0.12f);
    glVertex2f(baseX + 0.025f, baseY); glVertex2f(baseX + 0.008f, baseY + 0.11f);
    glVertex2f(baseX - 0.012f, baseY); glVertex2f(baseX - 0.025f, baseY + 0.1f);
    glVertex2f(baseX + 0.012f, baseY); glVertex2f(baseX + 0.025f, baseY + 0.09f);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(38, 105, 38);
    glVertex2f(baseX, baseY); glVertex2f(baseX, baseY + 0.14f);
    glVertex2f(baseX - 0.008f, baseY); glVertex2f(baseX - 0.015f, baseY + 0.09f);
    glVertex2f(baseX + 0.008f, baseY); glVertex2f(baseX + 0.015f, baseY + 0.08f);
    glEnd();
    
    // Night poppy
    float f1x = baseX - 0.03f, f1y = baseY + 0.07f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(24, 60, 24);
    glVertex2f(f1x, baseY); glVertex2f(f1x, f1y);
    glEnd();
    for (i = 0; i < 6; i++) {
        float angle = i * twicePi / 6 + 0.2f;
        glBegin(GL_POLYGON);
        glColor3ub(160, 25, 25);
        glVertex2f(f1x, f1y);
        glColor3ub(120, 15, 15);
        glVertex2f(f1x + 0.014f * cos(angle - 0.24f), f1y + 0.014f * sin(angle - 0.24f));
        glVertex2f(f1x + 0.02f * cos(angle), f1y + 0.02f * sin(angle));
        glVertex2f(f1x + 0.014f * cos(angle + 0.24f), f1y + 0.014f * sin(angle + 0.24f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(25, 25, 25);
    glVertex2f(f1x, f1y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f1x + 0.006f * cos(i * twicePi / 8), f1y + 0.006f * sin(i * twicePi / 8));
    }
    glEnd();
    
    // Night cornflower  
    float f2x = baseX + 0.03f, f2y = baseY + 0.08f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(28, 68, 28);
    glVertex2f(f2x, baseY); glVertex2f(f2x, f2y);
    glEnd();
    for (i = 0; i < 14; i++) {
        float angle = i * twicePi / 14;
        float len = (i % 2 == 0) ? 0.018f : 0.012f;
        glBegin(GL_TRIANGLES);
        glColor3ub(60, 80, 150);
        glVertex2f(f2x + 0.004f * cos(angle - 0.2f), f2y + 0.004f * sin(angle - 0.2f));
        glColor3ub(80, 110, 180);
        glVertex2f(f2x + len * cos(angle), f2y + len * sin(angle));
        glColor3ub(60, 80, 150);
        glVertex2f(f2x + 0.004f * cos(angle + 0.2f), f2y + 0.004f * sin(angle + 0.2f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(130, 80, 130);
    glVertex2f(f2x, f2y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f2x + 0.005f * cos(i * twicePi / 8), f2y + 0.005f * sin(i * twicePi / 8));
    }
    glEnd();
    
    // Night buttercup with moonlight sheen
    float f3x = baseX, f3y = baseY + 0.12f;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(32, 78, 32);
    glVertex2f(f3x, baseY); glVertex2f(f3x, f3y);
    glEnd();
    for (i = 0; i < 5; i++) {
        float angle = i * twicePi / 5 - PI/2;
        glBegin(GL_POLYGON);
        glColor3ub(180, 175, 40);
        glVertex2f(f3x, f3y);
        glColor3ub(150, 145, 20);
        glVertex2f(f3x + 0.012f * cos(angle - 0.26f), f3y + 0.012f * sin(angle - 0.26f));
        glColor3ub(190, 190, 120);
        glVertex2f(f3x + 0.017f * cos(angle), f3y + 0.017f * sin(angle));
        glColor3ub(150, 145, 20);
        glVertex2f(f3x + 0.012f * cos(angle + 0.26f), f3y + 0.012f * sin(angle + 0.26f));
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(110, 130, 45);
    glVertex2f(f3x, f3y);
    for (i = 0; i <= 8; i++) {
        glVertex2f(f3x + 0.004f * cos(i * twicePi / 8), f3y + 0.004f * sin(i * twicePi / 8));
    }
    glEnd();
}

void well()
{

    glBegin(GL_POLYGON);
    glColor3ub(204, 51, 0);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.9f, -0.55f);
    glVertex2f(-0.85f, -0.575f);
    glVertex2f(-0.8f, -0.59f);
    glVertex2f(-0.7f, -0.59f);
    glVertex2f(-0.65f, -0.575f);
    glVertex2f(-0.6f, -0.55f);
    glVertex2f(-0.6f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 102, 51);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.85f, -0.375f);
    glVertex2f(-0.8f, -0.38f);
    glVertex2f(-0.7f, -0.38f);
    glVertex2f(-0.65f, -0.375f);
    glVertex2f(-0.6f, -0.35f);
    glVertex2f(-0.65f, -0.33f);
    glVertex2f(-0.7f, -0.325f);
    glVertex2f(-0.8f, -0.325f);
    glVertex2f(-0.85f, -0.33f);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(204, 51, 0);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.85f, -0.33f); //
    glVertex2f(-0.85f, -0.33f);
    glVertex2f(-0.8f, -0.325f); //
    glVertex2f(-0.8f, -0.325f);
    glVertex2f(-0.7f, -0.325f); //
    glVertex2f(-0.7f, -0.325f);
    glVertex2f(-0.65f, -0.33f); //
    glVertex2f(-0.65f, -0.33f);
    glVertex2f(-0.6f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(194, 194, 163);
    glVertex2f(-0.59f, -0.43f);
    glVertex2f(-0.57f, -0.5f);
    glVertex2f(-0.52f, -0.5f);
    glVertex2f(-0.5f, -0.43f);
    glVertex2f(-0.52f, -0.42f);
    glVertex2f(-0.57f, -0.42f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(-0.585f, -0.43f);
    glVertex2f(-0.568f, -0.44f);
    glVertex2f(-0.528f, -0.44f);
    glVertex2f(-0.505f, -0.43f);
    glVertex2f(-0.528f, -0.425f);
    glVertex2f(-0.57f, -0.425f);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(194, 194, 163);
    glVertex2f(-0.59f, -0.43f);
    glVertex2f(-0.57f, -0.39f); //
    glVertex2f(-0.57f, -0.39f);
    glVertex2f(-0.55f, -0.39f); //
    glVertex2f(-0.55f, -0.39f);
    glVertex2f(-0.52f, -0.39f); //
    glVertex2f(-0.52f, -0.39f);
    glVertex2f(-0.5f, -0.43f); //
    glEnd();

    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor3ub(230, 172, 0);
    glVertex2f(-0.545f, -0.385f);
    glVertex2f(-0.57f, -0.45f); //
    glVertex2f(-0.57f, -0.45f);
    glVertex2f(-0.575f, -0.5f); //
    glVertex2f(-0.575f, -0.5f);
    glVertex2f(-0.58f, -0.53f); //
    glVertex2f(-0.58f, -0.53f);
    glVertex2f(-0.57f, -0.55f); //
    glVertex2f(-0.57f, -0.55f);
    glVertex2f(-0.48f, -0.53f); //
    glEnd();
}

void well1()
{

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(204, 51, 0);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.85f, -0.33f); //
    glVertex2f(-0.85f, -0.33f);
    glVertex2f(-0.8f, -0.325f); //
    glVertex2f(-0.8f, -0.325f);
    glVertex2f(-0.7f, -0.325f); //
    glVertex2f(-0.7f, -0.325f);
    glVertex2f(-0.65f, -0.33f); //
    glVertex2f(-0.65f, -0.33f);
    glVertex2f(-0.6f, -0.35f);
    glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(194, 194, 163);
    glVertex2f(-0.59f, -0.43f);
    glVertex2f(-0.57f, -0.39f); //
    glVertex2f(-0.57f, -0.39f);
    glVertex2f(-0.55f, -0.39f); //
    glVertex2f(-0.55f, -0.39f);
    glVertex2f(-0.52f, -0.39f); //
    glVertex2f(-0.52f, -0.39f);
    glVertex2f(-0.5f, -0.43f); //
    glEnd();

    glLineWidth(2.5);
    glBegin(GL_LINES);
    glColor3ub(230, 172, 0);
    glVertex2f(-0.545f, -0.385f);
    glVertex2f(-0.57f, -0.45f); //
    glVertex2f(-0.57f, -0.45f);
    glVertex2f(-0.575f, -0.5f); //
    glVertex2f(-0.575f, -0.5f);
    glVertex2f(-0.58f, -0.53f); //
    glVertex2f(-0.58f, -0.53f);
    glVertex2f(-0.57f, -0.55f); //
    glVertex2f(-0.57f, -0.55f);
    glVertex2f(-0.48f, -0.53f); //
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 154, 214);
    glVertex2f(-0.585f, -0.43f);
    glVertex2f(-0.568f, -0.44f);
    glVertex2f(-0.528f, -0.44f);
    glVertex2f(-0.505f, -0.43f);
    glVertex2f(-0.528f, -0.425f);
    glVertex2f(-0.57f, -0.425f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(204, 51, 0);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.9f, -0.55f);
    glVertex2f(-0.85f, -0.575f);
    glVertex2f(-0.8f, -0.59f);
    glVertex2f(-0.7f, -0.59f);
    glVertex2f(-0.65f, -0.575f);
    glVertex2f(-0.6f, -0.55f);
    glVertex2f(-0.6f, -0.35f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 102, 51);
    glVertex2f(-0.9f, -0.35f);
    glVertex2f(-0.85f, -0.375f);
    glVertex2f(-0.8f, -0.38f);
    glVertex2f(-0.7f, -0.38f);
    glVertex2f(-0.65f, -0.375f);
    glVertex2f(-0.6f, -0.35f);
    glVertex2f(-0.65f, -0.33f);
    glVertex2f(-0.7f, -0.325f);
    glVertex2f(-0.8f, -0.325f);
    glVertex2f(-0.85f, -0.33f);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(194, 194, 163);
    glVertex2f(-0.59f, -0.43f);
    glVertex2f(-0.57f, -0.5f);
    glVertex2f(-0.52f, -0.5f);
    glVertex2f(-0.5f, -0.43f);
    glVertex2f(-0.52f, -0.42f);
    glVertex2f(-0.57f, -0.42f);
    glEnd();
}
void StartingText()
{
    char text[120];
    // Title - bigger font, centered
    sprintf(text, "RIVER VIEW", 5.00, 8.00);
    glColor3f(0, 0, 0);
    glRasterPos2f(-22, 18);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    // Subtitle
    sprintf(text, "Beautiful Village Scenario", 5.00, 8.00);
    glRasterPos2f(-32, 12);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    // Keyboard shortcuts as bullet points
    glColor3f(0, 0, 0);
    sprintf(text, "Keyboard Shortcuts:");
    glRasterPos2f(-40, 4);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   D - Day View");
    glRasterPos2f(-40, -2);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   N - Night View");
    glRasterPos2f(-40, -8);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   R - Rain View");
    glRasterPos2f(-40, -14);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    // Team section
    sprintf(text, "Team Members:");
    glRasterPos2f(-40, -24);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   Md Rijoan Maruf (23-53347-3)");
    glRasterPos2f(-40, -30);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   Sadia Islam Anusha (23-55670-3)");
    glRasterPos2f(-40, -36);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    sprintf(text, "   Jakiya Sultana Meduli (23-55439-3)");
    glRasterPos2f(-40, -42);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void DrawSphere()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(position2, 0.0f, 0.0f);
    cloud3();
    glPopMatrix();
    moon();
    // sun();
    boat4();
    boat3();
    hut1();
    tree();
    backgroundtree();
    fence();
    grass4();
    grass5();
    grass6();
    way();
    well1();
    Straw();
    ground();
    river();
    glPushMatrix();
    glTranslatef(0.0f, position4, 0.0f);
    sun();
    glPopMatrix();
    stars();
    sky2();
    glFlush();
}

void display2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    PointLight(0, 0, 1, 0, 1, 1);
    DrawSphere();
    glLoadIdentity();
    glutSwapBuffers();
}

struct Point
{
    float x, y;
    unsigned char r, g, b, a;
};

#define MAX_RAIN_POINTS 1000
Point points[MAX_RAIN_POINTS];
int numPoints = 0;

void display1(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLineWidth(2);
    
    // Use stormy rain sky with lightning effect
    skyRain();
    
    // Dark storm clouds
    cloud1();
    cloud2();
    cloud3();
    backgroundtree();
    
    // River with rain effect - darker and more reflective
    river();
    
    // Draw rain puddles
    drawRainPuddles();
    
    ground();
    grass1();
    grass2();
    grass3();
    way();
    boat2();
    fence();
    tree();
    well();
    Straw();
    hut();
    
    // Draw ambient lighting overlay when lightning flashes
    if (lightningActive && lightningBrightness > 0.1f) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glColor4f(0.9f, 0.95f, 1.0f, lightningBrightness * 0.15f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
        glDisable(GL_BLEND);
    }
    
    glOrtho(-50, 50, -50, 50, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // draw rain drops
    glPushMatrix();
    glTranslatef(0.0f, position3, 0.0f);
    
    // Rain drops with varying brightness based on lightning
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(Point), &points[0].x);
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Point), &points[0].r);
    glPointSize(2.5);
    glDrawArrays(GL_POINTS, 0, numPoints);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLineWidth(2);
    sky();
    sun();
    glPushMatrix();
    glTranslatef(position2, 0.0f, 0.0f);
    cloud1();
    cloud2();
    glPopMatrix();
    // Birds now handle their own positions with animated wings
    bird();
    backgroundtree();
    river();
    glPushMatrix();
    glTranslatef(position1, 0.0f, 0.0f);
    boat();
    glPopMatrix();
    ground();
    grass1();
    grass2();
    grass3();
    way();
    boat2();
    fence();
    tree();
    well();
    Straw();
    hut();
    glFlush();
    glutSwapBuffers();
}
void reshape(int w, int h)
{
    //    std::cout<<"Reshape is called"<<std::endl;
    float aspectRatio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(145, aspectRatio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Display(void)
{
    // std::cout<<"Display 1 called"<<std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -20);
    StartingText();
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHT0);
    // std::cout<<"Init is called"<<std::endl;
}
void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display);
        PlaySound(TEXT("bird-2.wav"), NULL, SND_ASYNC);
        break;
        break;
    case 'r':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display1);
        PlaySound(TEXT("rain-07.wav"), NULL, SND_ASYNC);
        break;
    case 'n':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display2);
        PlaySound(TEXT("cricket-2.wav"), NULL, SND_ASYNC);
        glutPostRedisplay();
        break;
    case 'D':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display);
        PlaySound(TEXT("bird-2.wav"), NULL, SND_ASYNC);
        break;
        break;
    case 'R':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display1);
        PlaySound(TEXT("rain-07.wav"), NULL, SND_ASYNC);
        break;
    case 'N':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("village scenario");
        glutKeyboardFunc(handleKeypress);
        glutDisplayFunc(display2);
        PlaySound(TEXT("cricket-2.wav"), NULL, SND_ASYNC);
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1240, 750);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
    glutCreateWindow("village scenario");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(Display);
    for (int i = 0; i < MAX_RAIN_POINTS; ++i)
    {
        points[i].x = -50 + (rand() % 100);
        points[i].y = -50 + (rand() % 100);
        points[i].r = 255;
        points[i].g = 255;
        points[i].b = 255;
        points[i].a = 255;
    }
    numPoints = MAX_RAIN_POINTS;
    glutTimerFunc(100, cloud, 0);
    glutTimerFunc(100, sunn, 0);
    glutTimerFunc(100, boat, 0);
    glutTimerFunc(100, rain, 0);
    glutTimerFunc(100, birdd, 0);
    glutKeyboardFunc(handleKeypress);
    init();
    glutMainLoop();
    return 0;
}
