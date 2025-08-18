import base64

def upload_image(file_path, output_file):
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read())
    with open(output_file, "wb") as text_file:
        text_file.write(encoded_string)

# Example usage
upload_image("path_to_your_image.jpg", "encoded_image.txt")