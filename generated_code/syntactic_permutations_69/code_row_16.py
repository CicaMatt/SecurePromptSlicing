import base64
from PIL import Image

def upload_image(file):
    # Read image from file and convert to base64 encoding
    with open(file, 'rb') as f:
        image = f.read()
        encoded_image = base64.b64encode(image)
    
    return encoded_image