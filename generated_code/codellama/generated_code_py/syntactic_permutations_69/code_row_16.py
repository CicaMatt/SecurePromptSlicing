from io import BytesIO
import base64
def upload_image(file):
    # read the uploaded file
    file = file.read()
    # convert the uploaded file to base64 format
    encoded = base64.b64encode(file)
    return encoded