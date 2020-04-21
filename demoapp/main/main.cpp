#include "esp_event.h"

#include <LedMatrix.h>
#include <Line.h>
#include <Rect.h>

#define PIN 12
#define MATRIX_WIDTH 25
#define MATRIX_HEIGHT 16
#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

#ifdef __cplusplus
extern "C" {
#endif

void loop_squares(LedMatrix& matrix, uint16_t delay)
{
    // FIXME might break on matrices with odd number of pixels in vert/horiz direction

    const int iters = (MATRIX_WIDTH < MATRIX_HEIGHT ? MATRIX_WIDTH : MATRIX_HEIGHT) / 2;
    const int x = MATRIX_WIDTH / 2 - 1;
    const int y = MATRIX_HEIGHT / 2 - 1;
    const CRGB &color = CRGB(150, 150, 150);

    for (int n = 1; n < iters; ++n) {
        FastLED.clear();
        Rect(x - n, y - n, 2 * (n + 1), 2 * (n + 1), color).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
    for (int n = iters - 2; n >= 0; --n) {
        FastLED.clear();
        Rect(x-n, y-n, 2 * (n+1), 2 * (n+1), color).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
}

void app_main()
{
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    CRGB pixels[NUM_PIXELS];
    auto matrix = LedMatrix(CFastLED::addLeds<WS2812, PIN, GRB>(pixels, NUM_PIXELS),
                            MATRIX_WIDTH, MATRIX_HEIGHT, MatrixInvertHorizontal
    );
    FastLED.clear(true);
    FastLED.setBrightness(160);

    /******************************************************************************************************************/
    /* LINES */
//    ESP_LOGI("MatrixTest", "LINES...");
//
//    int lineDelay = 100;
//
//    Line(0, 0, MATRIX_WIDTH, 0, CRGB(120, 120, 0)).render(matrix);
//    Line(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB(180, 20, 60)).render(matrix);
//    Line(0, 0, 0, MATRIX_HEIGHT, CRGB(10, 20, 160)).render(matrix);
//    matrix.show();
//    FastLED.delay(1000);
//
//    for (int n = 0; n < MATRIX_WIDTH; ++n) {
//        FastLED.clear();
//        Line(0, 0, n, MATRIX_HEIGHT, CRGB(250, 0, 0)).render(matrix);
//        matrix.show();
//        FastLED.delay(lineDelay);
//    }
//    for (int n = MATRIX_HEIGHT-1; n >= 0; --n) {
//        FastLED.clear();
//        Line(0, 0, MATRIX_WIDTH, n, CRGB(250, 0, 0)).render(matrix);
//        matrix.show();
//        FastLED.delay(lineDelay);
//    }
//    for (int n = 0; n < MATRIX_HEIGHT; ++n) {
//        FastLED.clear();
//        Line(0, n, MATRIX_WIDTH, 0, CRGB(250, 0, 0)).render(matrix);
//        matrix.show();
//        FastLED.delay(lineDelay);
//    }
//    for (int n = 0; n < MATRIX_WIDTH; ++n) {
//        FastLED.clear();
//        Line(n, MATRIX_HEIGHT, MATRIX_WIDTH, 0, CRGB(250, 0, 0)).render(matrix);
//        matrix.show();
//        FastLED.delay(lineDelay);
//    }
//
//    FastLED.delay(1000);
    /******************************************************************************************************************/
    /* RECTS */
    ESP_LOGI("MatrixTest", "RECTS...");

    int rectDelay = 60;

//    FastLED.clear();
//    Rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB(0, 0, 255)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    for (int size = 1; size <= (MATRIX_WIDTH < MATRIX_HEIGHT ? MATRIX_WIDTH : MATRIX_HEIGHT); ++size) {
//        FastLED.clear();
//        Rect(0, 0, size, size, CRGB(0, 0, 255)).render(matrix);
//        matrix.show();
//        FastLED.delay(rectDelay);
//
//        FastLED.clear();
//        Rect(0, 0, size, size, CRGB(0, 0, 255)).setFillColor(CRGB(255, 0, 0)).render(matrix);
//        matrix.show();
//        FastLED.delay(rectDelay);
//    }
//
//    FastLED.clear();
//    Rect(5, 5, 5, 7, CRGB(0, 0, 255)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    FastLED.clear();
//    Rect(5, 5, 9, 3, CRGB(0, 0, 255)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    FastLED.clear();
//    Rect(0, 0, 20, 3, CRGB(0, 0, 255)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    FastLED.clear();
//    Rect(5, 5, 5, 7, CRGB(0, 0, 255)).setFillColor(CRGB(255, 0, 0)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    FastLED.clear();
//    Rect(5, 5, 9, 3, CRGB(0, 0, 255)).setFillColor(CRGB(255, 0, 0)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);
//
//    FastLED.clear();
//    Rect(0, 0, 20, 3, CRGB(0, 0, 255)).setFillColor(CRGB(255, 0, 0)).render(matrix);
//    matrix.show();
//    FastLED.delay(rectDelay);

//    while (true) {
//        FastLED.delay(rectDelay);
//        FastLED.clear();
//        for (int n = 0; n <= (MATRIX_WIDTH < MATRIX_HEIGHT ? MATRIX_WIDTH : MATRIX_HEIGHT) / 2; n += 2) {
//            Rect(n, n, MATRIX_WIDTH - 2 * n, MATRIX_HEIGHT - 2 * n,
//                 CRGB(30 * (n + 1), 30 * (n + 1), 30 * (n + 1))).render(matrix);
//            matrix.show();
//            FastLED.delay(rectDelay);
//        }
//    }

    while (true) {
        loop_squares(matrix, 25);
    }
}

#ifdef __cplusplus
} // extern "C"
#endif
