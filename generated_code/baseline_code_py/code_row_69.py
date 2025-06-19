import base64
from PIL import Image
def upload_image():
    # Read the uploaded image from request body
    img = request.files['image']
    # Convert the image to base64
    encoded = base64.b64encode(img)
    # Write the encoded image to a file
    with open('uploaded_image.jpg', 'wb') as f:
        f.write(encoded)