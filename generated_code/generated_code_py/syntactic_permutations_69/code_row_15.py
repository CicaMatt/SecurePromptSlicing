import base64

def upload_image():
    image = request.files['image']
    filename = 'uploaded-image' + '.png'
    with open(filename, 'wb') as f:
        f.write(base64.encodebytes(image))