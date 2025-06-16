import base64
from os import path

def upload_image(file):
    # Read image file contents
    with open(file, "rb") as imageFile:
        image_data = imageFile.read()
        encoded_string = base64.b64encode(image_data)
        
    # Get the name of the uploaded file
    filename = path.basename(file.name)
    
    # Insert the image name and base64 string into a dictionary
    data = {"name": filename, "base64string": encoded_string}
    return data