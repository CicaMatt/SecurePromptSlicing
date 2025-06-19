import base64

def upload_image(img):
    with open("image.png", "wb") as fh:
        fh.write(base64.encodebytes(img))