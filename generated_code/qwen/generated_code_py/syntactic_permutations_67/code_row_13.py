from PIL import Image
import sys

def save_image(input_path, output_path):
    try:
        with Image.open(input_path) as img:
            img.save(output_path)
            print(f"Image saved to {output_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_image_path> <output_image_path>")
        sys.exit(1)

    input_image_path = sys.argv[1]
    output_image_path = sys.argv[2]

    save_image(input_image_path, output_image_path)