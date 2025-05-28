import base64
def upload_image(file_name):
    with open(file_name, 'rb') as img_data:
        with open("encoded_file.txt", "wb") as encoded_img:
            data = base64.b64encode(img_data.read())
            encoded_img.write(data)
upload_image('test_image.jpg')