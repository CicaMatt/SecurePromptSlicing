import os, sys
from PIL import Image

def store_image(input_file):
    img = Image.open(input_file)
    # Save the image in the current working directory
    img.save('image.png')