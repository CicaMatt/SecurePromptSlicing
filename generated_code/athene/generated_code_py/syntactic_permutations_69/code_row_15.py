import base64

def upload_image(image_file):
    with open(image_file, 'rb') as img:
        img_data = img.read()
        encoded_img = base64.b64encode(img_data)
    
    with open('uploaded_image.txt', 'wb') as file:
        file.write(encoded_img)

upload_image('path/to/your/image.jpg')