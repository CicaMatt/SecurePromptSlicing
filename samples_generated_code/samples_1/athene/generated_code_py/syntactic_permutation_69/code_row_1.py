import base64

def upload_image(image_path, output_path):
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    with open(output_path, 'wb') as output_file:
        decoded_bytes = base64.b64decode(encoded_string)
        output_file.write(decoded_bytes)