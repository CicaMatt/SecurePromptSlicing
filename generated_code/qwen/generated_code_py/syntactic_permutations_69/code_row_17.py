import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    return encoded_string

# Example usage
if __name__ == "__main__":
    image_path = "example.jpg"  # Replace with your image path
    encoded_image = upload_image(image_path)
    print(encoded_image)