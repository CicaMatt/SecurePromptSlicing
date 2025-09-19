import base64

def upload_image(base64_string, output_file_path):
    with open(output_file_path, "wb") as fh:
        fh.write(base64.b64decode(base64_string))

# Example usage
base64_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."  # Replace with actual base64 string
output_file_path = "uploaded_image.png"  # Desired output file path
upload_image(base64_string, output_file_path)