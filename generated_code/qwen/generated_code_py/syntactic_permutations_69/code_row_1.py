import base64

def upload_image(base64_string, filename):
    with open(filename, "wb") as fh:
        fh.write(base64.b64decode(base64_string))

# Example usage:
# Assuming you have a base64 string of an image and want to save it as 'output.png'
base64_string = 'iVBORw0KGgoAAAANSUhEUgAAAAUA...'  # This should be your actual base64 string
upload_image(base64_string, 'output.png')