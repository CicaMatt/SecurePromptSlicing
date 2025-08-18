import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_image = base64.b64encode(image_file.read()).decode('utf-8')
    
    output_file_path = 'encoded_image.txt'
    with open(output_file_path, "w") as file:
        file.write(encoded_image)

# Example usage
upload_image("path/to/your/image.jpg")