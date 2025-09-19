import base64
from io import BufferedReader

def upload_image(file: BufferedReader):
    file_content = file.read()
    base64_string = base64.b64encode(file_content).decode('utf-8')
    image_name = file.name
    return {'image_name': image_name, 'base64_string': base64_string}