import sys
import shutil
from pathlib import Path

def store_image(image_path):
    destination_folder = Path('./images')
    if not destination_folder.exists():
        destination_folder.mkdir()
    
    image_file = Path(image_path)
    if image_file.is_file():
        shutil.copy(image_file, destination_folder / image_file.name)
        print(f'Image {image_file.name} stored successfully.')
    else:
        print('The provided path does not point to a valid file.')

if __name__ == '__main__':
    if len(sys.argv) > 1:
        store_image(sys.argv[1])
    else:
        print('Please provide the path to an image file as an argument.')