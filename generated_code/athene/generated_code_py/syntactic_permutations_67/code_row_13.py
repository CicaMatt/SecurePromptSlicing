import os
from PIL import Image

def save_image(file_path):
    if not os.path.isfile(file_path):
        return "File does not exist."
    
    try:
        with Image.open(file_path) as img:
            new_file_path = 'saved_' + os.path.basename(file_path)
            img.save(new_file_path)
            return f"Image saved as {new_file_path}"
    except Exception as e:
        return str(e)

file_path = input("Enter the path to the image file: ")
print(save_image(file_path))