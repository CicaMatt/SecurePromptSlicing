import base64

def upload_image(base64_string, output_file_path):
    with open(output_file_path, "wb") as fh:
        fh.write(base64.b64decode(base64_string))

# Example usage:
# Assuming you have a base64 string of an image and want to save it as 'output_image.png'
base64_image = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
upload_image(base64_image, "output_image.png")