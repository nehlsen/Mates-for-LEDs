#include "esp_event.h"

#include <LedMatrix.h>
#include <Line.h>
#include <Rect.h>
#include <Circle.h>
#include <Text.h>
//#include "../Shark/Shark.h"

//#define PIN 12
#define PIN 26
#define MATRIX_WIDTH 25
#define MATRIX_HEIGHT 16
#define NUM_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

#ifdef __cplusplus
extern "C" {
#endif

void demo_flash(LedMatrix& matrix)
{
    const int countDownFrom = 4;

    Text counter = Text(10, 5, "", CRGB(255, 255, 255));

    for (int countdown = countDownFrom; ; --countdown) {
        FastLED.clear();
        counter.setText(std::to_string(countdown)).render(matrix);
        matrix.show();

        for (int fade = 59; fade >= 0; --fade) {
            matrix.fade(245);
            FastLED.delay(17);
        }

        if (countdown == 1) {
            countdown = countDownFrom;

            auto oldBrightness = FastLED.getBrightness();
            FastLED.clear();
            FastLED.setBrightness(255);
            FastLED.showColor(CRGB(255, 255, 255));
            FastLED.delay(10);
            FastLED.clear();
            FastLED.delay(1000);
            FastLED.setBrightness(oldBrightness);
        }
    }
}

void test_rect_canvas(LedMatrix& matrix)
{
    Rect rect = Rect(0, 0, 2, 2, CRGB(255, 0, 0));

    for (int xTransform = 0; ; ++xTransform) {
        FastLED.clear();
        rect.setStart(xTransform, rect.getY0());
        GfxCanvas(rect).setCanvas(2, 2, 10, 7, GfxCanvas::CanvasClipping).render(matrix);
        matrix.show();
        FastLED.delay(300);

        if (xTransform == 12) { // TODO text.getTextWidth in pixels would be nice
            xTransform = -1;
        }
    }
}

void test_text_canvas(LedMatrix& matrix)
{
    Text text = Text(0, 0, "LEDs! ", CRGB(255, 0, 0));
    text.setCanvas(2, 2, 10, 7, Text::CanvasClipping);

    for (int xTransform = 0; ; ++xTransform) {
        FastLED.clear();
//        text.transform(-xTransform, 0).render(matrix);
        text.setX(-xTransform).render(matrix);
        matrix.show();
        FastLED.delay(300);

        if (xTransform == 12) { // TODO text.getTextWidth in pixels would be nice
            xTransform = -1;
        }
    }
}

void test_text(LedMatrix& matrix)
{
    FastLED.clear();
//    Text(0, 0, "HeLlo", CRGB(255, 0, 0)).render(matrix);
    Text(0, 0, "LEDs!", CRGB(255, 0, 0)).render(matrix);
    matrix.show();
}

void smiley(LedMatrix& matrix)
{
    const int x = MATRIX_WIDTH / 2 - 1;
    const int y = MATRIX_HEIGHT / 2 - 1;
    const int radius = (x < y ? x : y);
    const CRGB &smileyBgColor = CRGB(255, 170, 0);
    const CRGB &mouthColor = CRGB(255, 255, 127);
//    const CRGB &eyeColor = CRGB(0, 85, 250);
    const CRGB &eyeColor = mouthColor;
    const CRGB &smileyBorderColor = smileyBgColor;

    auto smileyBg = Circle(x, y, radius, smileyBorderColor).setFillColor(smileyBgColor);
    auto eyes = Rect(x + radius/2 - 1, y + radius/2, 2, 2, eyeColor).merge(Rect(x - radius/2, y + radius/2, 2, 2, eyeColor));
    auto mouth = Line(x - radius/2, y - radius/2, x + radius/2, y - radius/2, mouthColor);
    mouth.merge(Pixel(x - radius/2 - 1, y - radius/2 + 1, mouthColor));
    mouth.merge(Pixel(x + radius/2 + 1, y - radius/2 + 1, mouthColor));

    auto fullSmiley = smileyBg.merged(eyes).merged(mouth);

    FastLED.clear();
    fullSmiley.render(matrix);
    matrix.show();
}

//void shark(LedMatrix& matrix, uint16_t delay = 100)
//{
//    Shark shark;
//
//    int frame = 0;
//    while (true) {
////        for (int i = 0; i < FastLED.size(); i++) {
////            FastLED.leds()[i].nscale8(120);
////        }
//        FastLED.clear();
//
//        shark.setFrame(frame).render(matrix);
//        matrix.show();
//        FastLED.delay(delay);
//
//        frame++;
//        if (frame >= shark.getFrameCount()) {
//            frame = 0;
//        }
//    }
//}

void demo_lines(LedMatrix& matrix, uint16_t delay)
{
    const int long_delay = 5000;

    ESP_LOGI("MatrixTest", "LINES...");
    FastLED.clear();

    ESP_LOGI("MatrixTest", "0/0 -> w/0");
    Line(0, 0, MATRIX_WIDTH, 0, CRGB(120, 120, 0)).render(matrix);
    matrix.show();
    vTaskDelay(long_delay / portTICK_PERIOD_MS);

    ESP_LOGI("MatrixTest", "0/0 -> w/h");
    Line(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB(180, 20, 60)).render(matrix);
    matrix.show();
    vTaskDelay(long_delay / portTICK_PERIOD_MS);

    ESP_LOGI("MatrixTest", "0/0 -> 0/h");
    Line(0, 0, 0, MATRIX_HEIGHT, CRGB(10, 20, 160)).render(matrix);
    matrix.show();
    vTaskDelay(long_delay / portTICK_PERIOD_MS);

    ESP_LOGI("MatrixTest", "scan, 0/0 -> n/h");
    for (int n = 0; n < MATRIX_WIDTH; ++n) {
        FastLED.clear();
        Line(0, 0, n, MATRIX_HEIGHT, CRGB(250, 0, 0)).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
    ESP_LOGI("MatrixTest", "scan, 0/0 -> w/n");
    for (int n = MATRIX_HEIGHT-1; n >= 0; --n) {
        FastLED.clear();
        Line(0, 0, MATRIX_WIDTH, n, CRGB(250, 0, 0)).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
    ESP_LOGI("MatrixTest", "scan, 0/n -> w/0");
    for (int n = 0; n < MATRIX_HEIGHT; ++n) {
        FastLED.clear();
        Line(0, n, MATRIX_WIDTH, 0, CRGB(250, 0, 0)).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
    ESP_LOGI("MatrixTest", "scan, n/h -> w/0");
    for (int n = 0; n < MATRIX_WIDTH; ++n) {
        FastLED.clear();
        Line(n, MATRIX_HEIGHT, MATRIX_WIDTH, 0, CRGB(250, 0, 0)).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
    FastLED.delay(delay);
}

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

void white_rect(LedMatrix& matrix, uint16_t delay)
{
    matrix.clear();
    vTaskDelay(delay / portTICK_PERIOD_MS);

    const CRGB &white = CRGB(255, 255, 255);
    Rect rect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, white);
    rect.setFillColor(white);
    rect.render(matrix);
    matrix.show();
    vTaskDelay(delay / portTICK_PERIOD_MS);
}

void demo_rects(LedMatrix& matrix, uint16_t delay)
{
    ESP_LOGI("MatrixTest", "RECTS...");

    const CRGB lineColor(0, 0, 255);
    const CRGB fillColor(255, 0, 0);

    auto drawRect = [&](uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool fill = false) {
        ESP_LOGI("MatrixTest", "Rect, %d/%d : %d,%d, %s", x, y, width, height, (fill ? "solid" : "outline"));

        matrix.clear();

        Rect rect(x, y, width, height, lineColor);
        if (fill) rect.setFillColor(fillColor);
        rect.render(matrix);
        matrix.show();
//        FastLED.delay(delay);
        vTaskDelay(delay / portTICK_PERIOD_MS);
    };

    drawRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT);

    const int maxSize = std::min(MATRIX_WIDTH, MATRIX_HEIGHT);
    for (int size = 1; size <= maxSize; ++size) {
        drawRect(0, 0, size, size);
        drawRect(0, 0, size, size, true);
    }

    drawRect(5, 5, 5, 7);
    drawRect(5, 5, 9, 3);
    drawRect(0, 0, 20, 3);
    drawRect(5, 5, 5, 7, true);
    drawRect(5, 5, 9, 3, true);
    drawRect(0, 0, 20, 3, true);

//    while (true) {
//        FastLED.delay(delay);
//        FastLED.clear();
//        for (int n = 0; n <= (MATRIX_WIDTH < MATRIX_HEIGHT ? MATRIX_WIDTH : MATRIX_HEIGHT) / 2; n += 2) {
//            Rect(n, n, MATRIX_WIDTH - 2 * n, MATRIX_HEIGHT - 2 * n,
//                 CRGB(30 * (n + 1), 30 * (n + 1), 30 * (n + 1))).render(matrix);
//            matrix.show();
//            FastLED.delay(delay);
//        }
//    }
}

void drawCircles(LedMatrix& matrix, uint16_t delay)
{
    const int x = MATRIX_WIDTH / 2 - 1;
    const int y = MATRIX_HEIGHT / 2 - 1;
    const int radius = 7;
    const CRGB &borderColor = CRGB(250, 0, 0);
    const CRGB &fillColor = CRGB(0, 250, 0);

    FastLED.clear();
    Circle(x, y, radius, borderColor).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setQuarters(Circle::QuarterTopRight).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setQuarters(Circle::QuarterBottomRight).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setQuarters(Circle::QuarterBottomLeft).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setQuarters(Circle::QuarterTopLeft).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setFillColor(fillColor).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setFillColor(fillColor).setQuarters(Circle::QuarterTopRight).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setFillColor(fillColor).setQuarters(Circle::QuarterBottomRight).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setFillColor(fillColor).setQuarters(Circle::QuarterBottomLeft).render(matrix);
    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(x, y, radius, borderColor).setFillColor(fillColor).setQuarters(Circle::QuarterTopLeft).render(matrix);
    matrix.show();
    FastLED.delay(delay);
}

void draw_circles2(LedMatrix& matrix, uint16_t delay)
{
    FastLED.clear();
    Circle(3, 3, 2, CRGB(250, 0, 0)).setFillColor(CRGB(0, 250, 0)).render(matrix);
    Circle(5, 11, 3, CRGB(250, 0, 0)).setFillColor(CRGB(0, 250, 0)).render(matrix);
    Circle(18, 7, 6, CRGB(250, 0, 0)).setFillColor(CRGB(0, 250, 0)).render(matrix);

    matrix.show();
    FastLED.delay(delay);

    FastLED.clear();
    Circle(3, 3, 2, CRGB(250, 0, 0)).setQuarters(Circle::QuarterTopRight).setFillColor(CRGB(0, 250, 0)).render(matrix);
    Circle(5, 11, 3, CRGB(250, 0, 0)).setQuarters(Circle::QuarterBottomRight).setFillColor(CRGB(0, 250, 0)).render(matrix);
    Circle(18, 7, 6, CRGB(250, 0, 0)).setQuarters(Circle::QuarterTopLeft).setFillColor(CRGB(0, 250, 0)).render(matrix);

    matrix.show();
    FastLED.delay(delay);
}

void draw_circles3(LedMatrix& matrix, uint16_t delay)
{
    const int x = MATRIX_WIDTH / 2 - 1;
    const int y = MATRIX_HEIGHT / 2 - 1;
    const CRGB &borderColor = CRGB(250, 0, 0);
    const CRGB &fillColor = CRGB(0, 250, 0);

    for (int radius = 1; radius <= (x < y ? x : y); ++radius) {
        FastLED.clear();
        Circle(x, y, radius, borderColor).setFillColor(fillColor).render(matrix);
        matrix.show();
        FastLED.delay(delay);
    }
}

void draw_circles4(LedMatrix& matrix, uint16_t delay)
{
    const int x = MATRIX_WIDTH / 2 - 1;
    const int y = MATRIX_HEIGHT / 2 - 1;
    const int dropRadius = (x > y ? x : y) + 1;
    const int distance = 3;

    std::vector<Circle> circles(dropRadius/distance);
    for (int n = 0; n < circles.size(); ++n) {
        circles[n].setBorderColor(CRGB().setHue(random8()));
        circles[n].setCenter(x, y).setRadius((n+1)*distance);
    }

    ESP_LOGI("DEMO", "%d circles", circles.size());

    while (true) {
//        FastLED.clear();
        for (int i = 0; i < FastLED.size(); i++) {
            FastLED.leds()[i].nscale8(120);
        }

        for (Circle& c : circles) {
            if (c.getRadius() > dropRadius) {
                c.setRadius(0).setBorderColor(CRGB().setHue(random8()));;
            } else if (c.getRadius() > 0) {
                c.render(matrix);
            }

            c.setRadius(c.getRadius() + 1);
        }

        matrix.show();
        FastLED.delay(delay);
    }
}

void low_level_test(CRGB *pixels, uint16_t numPixels, uint16_t delay = 60)
{
    FastLED.clear();
    for (int i = 0; i < numPixels; ++i) {
        (pixels+i)->setRGB(255, 255, 255);
        FastLED.show();
        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

    FastLED.clear();
    FastLED.showColor(CRGB::White);
    vTaskDelay(delay / portTICK_PERIOD_MS);
}

void main_task(void *pvParameter)
{
    CRGB pixels[NUM_PIXELS];
//    CFastLED::addLeds<WS2812, PIN, GRB>(pixels, NUM_PIXELS);
    CFastLED::addLeds<WS2812B, 18, GRB>(pixels, 0, 133);
//    CFastLED::addLeds<WS2812B, 19, GRB>(pixels, 133, 267);
    CFastLED::addLeds<WS2812B, 19, GRB>(pixels, 133, 133);
    auto matrix = LedMatrix(FastLED, MATRIX_WIDTH, MATRIX_HEIGHT, MatrixInvertHorizontal);
    FastLED.clear(true);
    FastLED.setBrightness(160);

    while (true) low_level_test(&pixels[0], NUM_PIXELS);

    while (true) demo_lines(matrix, 100);

//    while (true) demo_rects(matrix, 500);
//    while (true) white_rect(matrix, 500);

//    while (true) drawCircles(matrix, 750);
//    while (true) draw_circles2(matrix, 2000);
//    while (true) draw_circles3(matrix, 100);
//    draw_circles4(matrix, 100);
//    shark(matrix);
//    smiley(matrix);
//    test_text(matrix);
//    test_text_canvas(matrix);
//    test_rect_canvas(matrix);
//    demo_flash(matrix);
}

void app_main()
{
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    xTaskCreatePinnedToCore(
            &main_task,
            "main_task",
            64 * 1024,
            nullptr,
            5,
            nullptr,
            0
    );
}

#ifdef __cplusplus
} // extern "C"
#endif
