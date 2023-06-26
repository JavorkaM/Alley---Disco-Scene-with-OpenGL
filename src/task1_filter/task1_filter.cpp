// Task 1 - Load a 512x512 image lena.raw
//        - Apply specified per-pixel transformation to each pixel
//        - Save as result.raw
#include <fstream>
#include <iostream>

// Size of the framebuffer
const unsigned int SIZE = 512;

// A simple RGB struct will represent a pixel in the framebuffer
struct Pixel {
  // TODO: Define correct data type for r, g, b channel
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

int main()
{
    // Initialize a framebuffer
    auto framebuffer = new Pixel[SIZE][SIZE];

    // TODO: Open file lena.raw (this is 512x512 RAW GRB format)
    std::ifstream image_stream("lena.raw", std::ios::binary);
    // TODO: Read data to framebuffer and close the file
    image_stream.read((char *) framebuffer, SIZE * SIZE  * sizeof(Pixel));
    image_stream.close();

    // Traverse the framebuffer
    for (unsigned int y = 0; y < SIZE; y++) {
        for (unsigned int x = 0; x < SIZE; x++) {
            framebuffer[y][x].r = (int)(framebuffer[y][x].r * x * -0.5) / 255;
            framebuffer[y][x].g = (int)(framebuffer[y][x].g * x * -0.5) / 255;
            framebuffer[y][x].b = (int)(framebuffer[y][x].b * x * -0.5) / 255;
        }
    }

    // TODO: Open file result.raw
    std::cout << "Generating result.raw file ..." << std::endl;
    std::ofstream image_out_stream("lenaOut.raw", std::ios::binary);

    // TODO: Write the framebuffer to the file and close it
    image_out_stream.write((char *) framebuffer, SIZE * SIZE  * sizeof(Pixel));
    image_out_stream.close();

    std::cout << "Done." << std::endl;
    delete[] framebuffer;
    return EXIT_SUCCESS;
}
