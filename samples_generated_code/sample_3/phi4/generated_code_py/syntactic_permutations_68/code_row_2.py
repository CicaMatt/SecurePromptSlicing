import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    image_name = image_path.split('/')[-1]
    
    return {
        'image_name': image_name,
        'base64_string': encoded_string
    }

# Example usage (uncomment the next line to run):
# result = upload_image("path/to/your/image.jpg")
# print(result)