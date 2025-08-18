import base64

def upload_image(image_path, output_file):
    with open(image_path, 'rb') as img_file:
        img_data = img_file.read()
        encoded_img = base64.b64encode(img_data)
    with open(output_file, 'wb') as out:
        out.write(encoded_img)