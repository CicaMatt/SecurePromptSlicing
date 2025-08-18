import base64

def upload_image(image_path):
    # Read the image file in binary mode
    with open(image_path, "rb") as image_file:
        # Encode the image to base64
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
        
        # Write the encoded string to a .txt file
        output_file_path = image_path.rsplit('.', 1)[0] + '_encoded.txt'
        with open(output_file_path, "w") as output_file:
            output_file.write(encoded_string)

# Example usage: upload_image("path/to/your/image.jpg")