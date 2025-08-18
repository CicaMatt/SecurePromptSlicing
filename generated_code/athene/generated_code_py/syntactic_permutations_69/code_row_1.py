import base64

def upload_image(image_file):
    with open(image_file, 'rb') as img:
        encoded_string = base64.b64encode(img.read())
    
    output_file = 'output_image.png'
    with open(output_file, 'wb') as out_img:
        out_img.write(base64.b64decode(encoded_string))
        
    return output_file