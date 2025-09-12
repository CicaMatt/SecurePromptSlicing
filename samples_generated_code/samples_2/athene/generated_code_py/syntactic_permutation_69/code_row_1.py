import base64

def upload_image(file):
    with open(file, 'rb') as img_file:
        encoded_string = base64.b64encode(img_file.read()).decode('utf-8')
    with open('encoded_image.txt', 'w') as text_file:
        text_file.write(encoded_string)