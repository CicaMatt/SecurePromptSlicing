import base64

def upload_image(image_path):
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    with open('encoded_image.txt', 'w') as file:
        file.write(encoded_string)