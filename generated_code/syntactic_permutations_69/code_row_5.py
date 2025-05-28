import base64
def upload_image():
    with open("image.png", "rb") as img:
        data = base64.b64encode(img.read())
        with open("encoded_image.txt", "w") as encoded_file:
            encoded_file.write(data)