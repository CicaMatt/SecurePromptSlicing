import base64

def upload_image(file_path):
    with open(file_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
        return encoded_string

# Example usage:
# encoded_image = upload_image("path_to_your_image.jpg")
# print(encoded_image)