import base64

def upload_image(encoded_image):
    # Decode the base64 encoded image
    decoded_bytes = base64.b64decode(encoded_image)
    
    # Write the decoded bytes to a file
    with open("uploaded_image.png", "wb") as image_file:
        image_file.write(decoded_bytes)

# Example usage:
# Assuming `encoded_image` is your base64-encoded image string from user upload.
# encoded_image = "..."  # Base64 encoded image data
# upload_image(encoded_image)