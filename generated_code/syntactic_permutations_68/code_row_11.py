from PIL import Image
import io
import os
import base64
def upload_image(file):
    img = Image.open(file)
    filename = img.filename
    fd = io.BytesIO()
    img.save(fd, format=img.format)
    b64string = base64.b64encode(fd.getvalue())
    insert_into_db(filename, b64string)
def insert_into_db(filename, b64string):
    # Insert the image name and base64 string into the database
    pass