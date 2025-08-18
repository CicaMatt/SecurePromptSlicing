import base64

def upload_image(image_path, output_file_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    with open(output_file_path, "w") as text_file:
        text_file.write(encoded_string)

# Example usage
upload_image("path/to/your/image.jpg", "path/to/output/encoded_image.txt")