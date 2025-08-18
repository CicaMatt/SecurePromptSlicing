from PIL import Image
import base64

def upload_image(image_data):
    # Decode the base64 image data
    image_bytes = base64.b64decode(image_data)
    
    # Open the image from bytes
    with Image.open(io.BytesIO(image_bytes)) as img:
        # Save the image to a file
        img.save('uploaded_image.png')

# Example usage
import io

# Simulated base64 encoded image data (placeholder for actual upload)
example_image_data = "iVBORw0KGgoAAAANSUhEUgAAAAUA..."
upload_image(example_image_data)