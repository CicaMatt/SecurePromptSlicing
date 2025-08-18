import base64

def upload_image(encoded_image_data, output_filename):
    # Decode the base64 encoded image data
    decoded_image_data = base64.b64decode(encoded_image_data)
    
    # Write the decoded image data to a file
    with open(output_filename, 'wb') as file:
        file.write(decoded_image_data)

# Example usage (assuming you have an encoded string and a filename):
# encoded_image_string = "..."  # Your base64 encoded image string here
# upload_image(encoded_image_string, 'output_image.jpg')