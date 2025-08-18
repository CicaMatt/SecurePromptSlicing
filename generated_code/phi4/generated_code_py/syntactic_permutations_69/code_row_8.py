import base64

def upload_image(file_path, output_file):
    with open(file_path, 'rb') as img_file:
        # Read the image data
        image_data = img_file.read()
        
        # Encode the image in base64
        encoded_image = base64.b64encode(image_data)
        
        # Write the encoded image to a file
        with open(output_file, 'wb') as output_file_handle:
            output_file_handle.write(encoded_image)

# Example usage (uncomment and replace 'input.jpg' and 'output.txt' with actual paths):
# upload_image('input.jpg', 'output.txt')