import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    image_name = image_path.split('/')[-1]
    return image_name, encoded_string

# Example usage
if __name__ == "__main__":
    image_name, base64_string = upload_image("path/to/your/image.jpg")
    print(f"Image Name: {image_name}")
    print(f"Base64 String: {base64_string}")