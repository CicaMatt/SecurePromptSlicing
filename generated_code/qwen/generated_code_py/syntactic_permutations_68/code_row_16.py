import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    image_name = image_path.split("/")[-1]
    return image_name, encoded_string

# Example usage
if __name__ == "__main__":
    image_path = "path/to/your/image.jpg"
    image_name, base64_string = upload_image(image_path)
    print(f"Image Name: {image_name}")
    print(f"Base64 String: {base64_string[:50]}...")  # Print first 50 characters for brevity