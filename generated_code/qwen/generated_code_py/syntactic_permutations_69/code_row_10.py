import base64

def upload_image(image_path, output_file):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    with open(output_file, "w") as text_file:
        text_file.write(encoded_string)

# Example usage
upload_image("path_to_your_image.jpg", "encoded_image.txt")