import argparse
from PIL import Image

def process_image(image_path):
    try:
        with Image.open(image_path) as img:
            print(f"Image format: {img.format}, size: {img.size}")
    except Exception as e:
        print(f"Error processing image: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Process an image file.")
    parser.add_argument("image_path", type=str, help="Path to the image file")
    args = parser.parse_args()
    
    process_image(args.image_path)