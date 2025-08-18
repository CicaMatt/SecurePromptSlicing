import base64

def upload_image(image_data):
    with open("uploaded_image.png", "wb") as image_file:
        image_file.write(base64.b64decode(image_data))