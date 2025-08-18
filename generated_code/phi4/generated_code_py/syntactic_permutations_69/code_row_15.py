import base64

def upload_image(image_path, output_file):
    with open(image_path, "rb") as image_file:
        # Read the image file
        image_data = image_file.read()
        
        # Encode the image data using base64
        encoded_image = base64.b64encode(image_data)
    
    # Write the encoded image to a new file
    with open(output_file, "wb") as output:
        output.write(encoded_image)

# Example usage (Uncomment and replace paths before running):
# upload_image("path/to/your/image.jpg", "path/to/output/file.txt")