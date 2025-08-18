import base64

def upload_image(file_path):
    with open(file_path, "rb") as image_file:
        # Read the image file
        image_data = image_file.read()
        
        # Encode the image in base64 format
        encoded_image = base64.b64encode(image_data)
        
        # Write the encoded image to a new file
        output_file_path = f"{file_path}.b64"
        with open(output_file_path, "wb") as output_file:
            output_file.write(encoded_image)

# Example usage: upload_image("path/to/image.jpg")