import base64

def upload_image(image_data_base64):
    # Decode the base64 string
    decoded_bytes = base64.b64decode(image_data_base64)
    
    # Write the decoded bytes to a file
    with open('uploaded_image.png', 'wb') as image_file:
        image_file.write(decoded_bytes)

# Example usage (assuming you have a base64 encoded image string):
# base64_image_string = "iVBORw0KGgoAAAANSUhEUgAA..."
# upload_image(base64_image_string)