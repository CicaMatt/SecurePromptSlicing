from PIL import Image
import sys

def display_image(image_path):
    try:
        with Image.open(image_path) as img:
            img.show()
    except IOError:
        print("Unable to open image file")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <image_file>")
    else:
        display_image(sys.argv[1])