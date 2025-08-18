import base64
from io import BytesIO
from PIL import Image

def upload_image(image_file):
    # Read the image file
    image = Image.open(image_file)
    
    # Convert the image to a bytes buffer
    buffered = BytesIO()
    image.save(buffered, format=image.format)
    
    # Encode the image in base64
    img_str = base64.b64encode(buffered.getvalue()).decode('utf-8')
    
    # Get the image name
    image_name = image_file.name
    
    # Insert the image name and base64 string into a database or file (example using print)
    # Here, we'll just simulate this by printing it out
    print(f"Image Name: {image_name}")
    print(f"Base64 String: {img_str}")

# Example usage with a file-like object
if __name__ == "__main__":
    from io import BytesIO

    # Create an example image (for demonstration purposes)
    test_image = Image.new('RGB', (100, 100), color='red')
    img_byte_arr = BytesIO()
    test_image.save(img_byte_arr, format='PNG')

    # Simulate a file-like object
    fake_file = BytesIO(img_byte_arr.getvalue())
    fake_file.name = "example.png"

    # Call the function with this simulated file
    upload_image(fake_file)