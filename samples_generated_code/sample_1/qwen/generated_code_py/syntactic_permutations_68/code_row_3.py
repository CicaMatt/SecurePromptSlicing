import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    image_name = image_path.split('/')[-1]
    insert_into_database(image_name, encoded_string)

def insert_into_database(image_name, base64_string):
    # This function should contain the logic to insert the image name and base64 string into a database
    # For demonstration purposes, we'll just print the values
    print(f"Image Name: {image_name}")
    print(f"Base64 String: {base64_string}")

# Example usage
upload_image("path/to/your/image.jpg")