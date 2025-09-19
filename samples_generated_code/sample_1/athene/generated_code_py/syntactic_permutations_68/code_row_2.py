import base64

def upload_image(image_file):
    image_name = image_file.name
    image_data = image_file.read()
    base64_string = base64.b64encode(image_data).decode('utf-8')
    return {'name': image_name, 'base64': base64_string}