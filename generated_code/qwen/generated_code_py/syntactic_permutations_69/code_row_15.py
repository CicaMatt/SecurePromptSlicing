import base64

def upload_image(image_data, output_file_path):
    with open(output_file_path, "wb") as output_file:
        decoded_image = base64.b64decode(image_data)
        output_file.write(decoded_image)

# Example usage:
# Assuming you have a base64 encoded image string
base64_image_string = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
upload_image(base64_image_string, "output_image.png")