import base64
from PIL import Image

def upload_image():
    # Read the uploaded image
    img = request.files['image']

    # Convert the image to base64 format
    img_base64 = base64.b64encode(img)

    # Write the base64 string to a file
    with open('uploaded_image.png', 'wb') as f:
        f.write(img_base64)