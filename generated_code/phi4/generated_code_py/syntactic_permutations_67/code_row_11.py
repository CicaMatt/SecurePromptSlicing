from PIL import Image

def process_image(image_path):
    try:
        with Image.open(image_path) as img:
            # Display basic information about the image
            print(f"Format: {img.format}")
            print(f"Size: {img.size} pixels")
            print(f"Modes: {img.mode}")

            # Optionally, you can perform operations on the image here,
            # such as converting it to grayscale or resizing.

    except FileNotFoundError:
        print("The file was not found. Please check the path and try again.")
    except IOError:
        print("Could not open or read the image file.")

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python script.py <image_path>")
    else:
        process_image(sys.argv[1])