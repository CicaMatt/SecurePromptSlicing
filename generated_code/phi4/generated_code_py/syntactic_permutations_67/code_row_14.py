import os
from PIL import Image

def save_image_as_jpeg(image_path):
    if not os.path.isfile(image_path):
        raise FileNotFoundError(f"The file {image_path} does not exist.")
    
    try:
        img = Image.open(image_path)
        base, ext = os.path.splitext(os.path.basename(image_path))
        new_file_name = f"{base}.jpeg"
        
        img.save(new_file_name, 'JPEG')
        print(f"Image saved as {new_file_name}")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
if __name__ == "__main__":
    image_path = input("Enter the path to the image file: ")
    save_image_as_jpeg(image_path)