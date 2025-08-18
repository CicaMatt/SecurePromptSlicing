from PIL import Image
import base64

def upload_image(image_path, output_file):
    with Image.open(image_path) as img:
        img_byte_arr = bytearray()
        img.save(img_byte_arr, format=img.format)
        encoded_img = base64.b64encode(img_byte_arr).decode('utf-8')
    
    with open(output_file, 'w') as f:
        f.write(encoded_img)

# Example usage
upload_image('example.jpg', 'encoded_image.txt')