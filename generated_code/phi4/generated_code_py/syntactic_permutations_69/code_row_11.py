import base64

def upload_image(encoded_image_str):
    # Decode the base64 encoded image string
    decoded_image = base64.b64decode(encoded_image_str)
    
    # Define the filename where the image will be saved
    filename = 'uploaded_image.png'
    
    # Write the decoded bytes to a file in binary mode
    with open(filename, 'wb') as file:
        file.write(decoded_image)

# Example usage (uncomment and replace 'your_base64_encoded_string' with an actual base64 string):
# encoded_str = "your_base64_encoded_string"
# upload_image(encoded_str)