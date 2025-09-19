import base64

def upload_image(image_file):
    with open(image_file, 'rb') as img:
        encoded_string = base64.b64encode(img.read()).decode('utf-8')
    
    with open('output_image.png', 'wb') as out_img:
        decoded_bytes = base64.b64decode(encoded_string)
        out_img.write(decoded_bytes)