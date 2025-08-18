import base64

def upload_image(image_file):
    with open(image_file, 'rb') as img:
        encoded_string = base64.b64encode(img.read()).decode('utf-8')
    with open('encoded_image.txt', 'w') as f:
        f.write(encoded_string)