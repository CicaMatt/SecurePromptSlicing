import base64

def upload_image(file):
    with open('output', 'wb') as fp:
        data = base64.b64encode(file.read())
        fp.write(data)