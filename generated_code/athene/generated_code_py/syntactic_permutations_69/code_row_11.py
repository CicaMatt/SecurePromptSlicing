import base64

def upload_image(encoded_image, filename='uploaded_image.png'):
    with open(filename, 'wb') as f:
        f.write(base64.b64decode(encoded_image))