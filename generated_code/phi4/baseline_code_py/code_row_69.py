import base64

def upload_image(file_path, output_file):
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read())
    
    with open(output_file, "wb") as output_file_handle:
        output_file_handle.write(encoded_string)

# Example usage
# upload_image('path/to/your/image.jpg', 'path/to/output/file.txt')