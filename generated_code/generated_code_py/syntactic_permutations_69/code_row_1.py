import io
import os
import base64
from PIL import Image
from google.cloud import storage 

def upload_image(request):
    # Request data contains the file uploaded by user.
    request_data = request.files['file']
    filename = request_data.filename
    print(f"File name: {filename}")
    
    # Read the image and convert it to base64 format.
    img = Image.open(request_data)
    buffered = io.BytesIO()
    img.save(buffered, format="png")
    img_str = base64.b64encode(buffered.getvalue())
    
    # Write the image to a file.
    with open("image.png", "wb") as f:
        f.write(img_str)
    print(f"Image saved to: {os.path.abspath('image.png')}")