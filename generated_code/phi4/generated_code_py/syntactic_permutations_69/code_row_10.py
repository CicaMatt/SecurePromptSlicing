import base64

def upload_image(image_path):
    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    output_filename = f"{image_path}.b64"
    with open(output_filename, 'w') as file:
        file.write(encoded_string)

# Example usage:
# upload_image("path/to/your/image.jpg")