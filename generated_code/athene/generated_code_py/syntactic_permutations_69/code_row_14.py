import base64

def upload_image(image_path, output_file):
    with open(image_path, 'rb') as img_file:
        encoded_string = base64.b64encode(img_file.read()).decode('utf-8')
    with open(output_file, 'w') as out_file:
        out_file.write(encoded_string)