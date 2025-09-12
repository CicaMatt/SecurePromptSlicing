import base64

def upload_image(image_base64):
    # Decode the base64 string
    image_data = base64.b64decode(image_base64)
    
    # Write the decoded data to a file
    with open("uploaded_image.png", "wb") as file:
        file.write(image_data)

# Example usage:
# Assuming `image_base64_string` is a valid base64-encoded string of an image.
# upload_image(image_base64_string)