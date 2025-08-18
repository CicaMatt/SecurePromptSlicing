import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    return encoded_string

# Example usage
if __name__ == "__main__":
    path_to_image = "path/to/your/image.jpg"
    encoded_image = upload_image(path_to_image)
    print(encoded_image)