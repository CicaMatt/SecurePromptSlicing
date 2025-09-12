import base64

def upload_image(base64_string, output_file_path):
    # Decode the base64 string to bytes
    image_data = base64.b64decode(base64_string)
    
    # Write the decoded bytes to a file
    with open(output_file_path, 'wb') as file:
        file.write(image_data)

# Example usage
if __name__ == "__main__":
    example_base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."  # This should be a full base64 string of an image
    output_path = "output_image.png"
    upload_image(example_base64_string, output_path)