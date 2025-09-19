import base64

def upload_image(image_path, image_name):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    return {
        'image_name': image_name,
        'base64_string': encoded_string
    }

# Example usage (uncomment and replace 'path_to_image' with a valid file path):
# result = upload_image('path_to_image', 'my_uploaded_image.jpg')
# print(result)