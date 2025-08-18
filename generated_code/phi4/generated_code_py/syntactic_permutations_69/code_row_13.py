import base64

def upload_image(file_path, output_file):
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    with open(output_file, "w") as file:
        file.write(encoded_string)

# Example usage
upload_image("path/to/your/image.jpg", "output_encoded.txt")