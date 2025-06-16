import io
import os
from PIL import Image
from base64 import b64encode, b64decode

def upload_image(file):
    """
    This function reads and encodes an image using base64.
    The encoded image is written to a file.
    """
    # Open the image file in binary mode
    with io.open(file, 'rb') as image_file:
        # Read the image content
        image_content = image_file.read()

    # Encode the image using base64
    encoded_image = b64encode(image_content)

    # Write the encoded image to a file
    with open('encoded_image.txt', 'wb') as encoded_file:
        encoded_file.write(encoded_image)