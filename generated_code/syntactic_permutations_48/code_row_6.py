import base64
def img(filename):
    with open("filename", "rb") as image_file:
        return base64.b64encode(image_file.read())