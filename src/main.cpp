#include "raylib.h"
#include "complex.h"

const int maxIterations = 100; // Maximum number of iterations used for Mandelbrot set

/*
 * @brief   Get color based on iteration count.
 *          Allows you to create a color gradient.
 * @param   iteration   Number of iterations for the pixel.
 * @return  Color for the pixel based on the iteration count.
 */
Color GetColorForIteration(int iteration) {
    if (iteration == maxIterations) return BLACK;

    float t = (float)iteration / maxIterations;
    unsigned char r = (unsigned char)(9 * (1 - t) * t * t * t * 255);
    unsigned char g = (unsigned char)(15 * (1 - t) * (1 - t) * t * t * 255);
    unsigned char b = (unsigned char)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    return Color{ r, g, b, 255 };
}

/*
 * @brief   Calculate and draw Mandelbrot set on the given image.
 * @param   image   Image to draw Mandelbrot set on.
 * @param   min     Minimum complex number defining the Mandelbrot set boundary.
 * @param   max     Maximum complex number defining the Mandelbrot set boundary.
 */
void CalculateMandelbrotSet(Image &image, const Complex &min, const Complex &max)
{
    int width = image.width;
    int height = image.height;

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Complex c(min.real + x * (max.real - min.real) / width, min.imaginary + y * (max.imaginary - min.imaginary) / height);
            Complex z(0, 0);
            int iteration = 0;

            while (z.abs() <= 2 && iteration < maxIterations)
            {
                z = z * z + c;
                ++iteration;
            }

            Color pixelColor = (iteration == maxIterations) ? BLACK : GetColorForIteration(iteration);
            ImageDrawPixel(&image, x, y, pixelColor);
        }
    }
}

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Mandelbrot Set - raylib");

    // Generate a black color image with specified dimensions
    Image mandelbrotImage = GenImageColor(screenWidth, screenHeight, BLACK);

    Complex min(-2.0, -1.5);
    Complex max(1.0, 1.5);

    // Calculate Mandelbrot set and draw it on the image
    CalculateMandelbrotSet(mandelbrotImage, min, max);

    Texture2D texture = LoadTextureFromImage(mandelbrotImage);  // Convert image to texture required for display in window
    UnloadImage(mandelbrotImage);   // Free memory occupied by the image

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}