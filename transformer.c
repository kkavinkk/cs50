#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// -f is to flip the image
// -s is to apply sepia

typedef struct {
    int r, g, b;
} Pixel;

// apply sepia filter
void sepia(Pixel *p) {
    int og_R = p->r;
    int og_G = p->g;
    int og_B = p->b;

    int R = og_R * 393 / 1000 + og_G * 769 / 1000 + og_B * 189 / 1000;
    int G = og_R * 349 / 1000 + og_G * 686 / 1000 + og_B * 168 / 1000;
    int B = og_R * 272 / 1000 + og_G * 534 / 1000 + og_B * 131 / 1000;

    p->r = (R > 255) ? 255 : R;
    p->g = (G > 255) ? 255 : G;
    p->b = (B > 255) ? 255 : B;
}

// flip a row of pixels horizontally
void flip(Pixel *row, int width) {
    for (int i = 0; i < width / 2; i++) {
        Pixel temp = row[i];
        row[i] = row[width - 1 - i];
        row[width - 1 - i] = temp;
    }
}

int main(int argc, char *argv[]) {
    int flip_f = 0, sepia_s = 0;

    // parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) flip_f = 1;
        else if (strcmp(argv[i], "-s") == 0) sepia_s = 1;
    }

    // read PPM header
    char type[3];
    int width, height, maxval;
    scanf("%2s", type);
    scanf("%d %d", &width, &height);
    scanf("%d", &maxval);

    // allocate memory for the image
    Pixel **image = malloc(height * sizeof(Pixel *));
    for (int i = 0; i < height; i++) {
        image[i] = malloc(width * sizeof(Pixel));
    }

    // read pixel data
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            scanf("%d %d %d", &image[i][j].r, &image[i][j].g, &image[i][j].b);
        }
    }

    // apply transformations
    for (int i = 0; i < height; i++) {
        if (flip_f) flip(image[i], width);
        for (int j = 0; j < width; j++) {
            if (sepia_s) sepia(&image[i][j]);
        }
    }

    // print PPM header
    printf("P3\n%d %d\n255\n", width, height);
    // print pixel data
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d %d %d", image[i][j].r, image[i][j].g, image[i][j].b);
            if (j < width - 1) printf(" ");
        }
        printf("\n");
    }

    // free memory
    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);

    return 0;
}
