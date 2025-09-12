import base64

def upload_image(image_path, output_file_path):
    with open(image_path, 'rb') as image_file:
        # Read the image data in binary mode
        image_data = image_file.read()
        
        # Encode the image data using base64
        encoded_image = base64.b64encode(image_data)
        
        # Write the encoded image to a file
        with open(output_file_path, 'wb') as output_file:
            output_file.write(encoded_image)

# Example usage:
# upload_image('path/to/your/image.jpg', 'path/to/output/file.txt')