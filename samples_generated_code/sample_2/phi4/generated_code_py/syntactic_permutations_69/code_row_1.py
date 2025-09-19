import base64

def upload_image(image_base64, output_file_path):
    # Decode the base64 string to bytes
    image_data = base64.b64decode(image_base64)
    
    # Write the image data to a file
    with open(output_file_path, 'wb') as file:
        file.write(image_data)

# Example usage (comment this out when integrating into your application):
# image_base64_string = "your_base64_encoded_image_string_here"
# output_path = "output_image.jpg"
# upload_image(image_base64_string, output_path)