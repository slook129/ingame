#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <Windows.h>

const float PI = 3.1415926f;


struct Sphere {
    float centrx, centry, centrz, radius;
    std::vector<float> verticies = {};
    void build(float x, float y, float z, float r) {

        this->centrx = x;
        this->centry = y;
        this->centrz = z;
        this->radius = r;
        verticies.clear();
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                j++;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                i++;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);

                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                j--;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                i--;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);

            }
        }

    }
    void draw() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, verticies.data());
        glDrawArrays(GL_TRIANGLES, 0, verticies.size() / 3);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    void movetick(Sphere* earth, float i, float j, float r, float speed) {
        this->build(cosf(i) * sinf(j) * r + earth->centrx,
            sinf(i) * sinf(j) * r + earth->centry,
            earth->centrz + r * cosf(j),
            this->radius);
    }
};

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Glew is not ok\n";
    }
    Sphere earth, moon;
    earth.build(0.0f, 0.0f, -0.2f, 0.125f);
    moon.build(0.0f, 0.0f, -0.6f, 0.0625f);
    glViewport(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);
    float fi = 0;
    float fang, sang, r, speed;
    std::cin >> fang >> sang >> r >> speed;
    fang = 2 * PI / 360;
    sang = 2 * PI / 360;
    speed = 1000 / speed;
    float fx = cosf(fang) * sinf(sang), fy = sinf(fang) * sinf(sang), fz = cosf(sang);
    float nz = sinf(sang), nx = 1.0f, ny = -1.0f;
    float nr = sqrtf(nx * nx + ny * ny + nz * nz);
    nx /= nr;
    ny /= nr;
    nz /= nr;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3ub(255, 0, 0);
        earth.draw();
        glColor3ub(0, 255, 0);
        fi += PI * 2 / speed;
        moon.build(earth.centrx + (fx * cosf(fi) + (fz * ny - fy * nz) * sinf(fi)) * r,
            earth.centrx + (fy * cosf(fi) + (fx * nz - fz * nx) * sinf(fi)) * r,
            earth.centrz + (fz * cosf(fi) + (fy * nx - fx * ny) * sinf(fi)) * r,
            0.0625f);
        moon.draw();
        Sleep(10);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}