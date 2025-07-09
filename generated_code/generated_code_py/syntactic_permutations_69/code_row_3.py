import base64
from io import BytesIO

def upload_image():
    file = request.files['image']
    if file:
        img_data = BytesIO(file.read())
        encoded_string = base64.b64encode(img_data)
        with open("imageToSave.txt", "w") as fh:
            fh.write(encoded_string)