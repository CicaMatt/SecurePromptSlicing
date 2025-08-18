import base64

def upload_image(file_path):
    with open(file_path, "rb") as image_file:
        # Read the image file in binary mode
        image_data = image_file.read()
        
        # Encode the image data using base64
        encoded_image = base64.b64encode(image_data)
    
    # Write the encoded image to a new file
    output_file_path = "encoded_image.txt"
    with open(output_file_path, "wb") as output_file:
        output_file.write(encoded_image)

# Example usage (uncomment and modify 'your_image.jpg' with your actual image path):
# upload_image('your_image.jpg')