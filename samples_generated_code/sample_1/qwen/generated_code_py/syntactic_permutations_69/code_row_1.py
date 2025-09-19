import base64

def upload_image(image_data):
    # Decode the base64 encoded image data
    decoded_image = base64.b64decode(image_data)
    
    # Write the decoded image to a file
    with open('uploaded_image.png', 'wb') as image_file:
        image_file.write(decoded_image)

# Example usage
if __name__ == "__main__":
    # This is an example of base64 encoded string for a small black square image
    example_base64_image = "/9j/2wBDAAYEBQYFBAYGBQYHBwYIChAKCgkJChQODwwQFxQYGBcUFhYaHSUfGhsjHBYWICwgIyYnKSopGR8tMC0oMCUoKSj/2wBDAQcHBwoIChMKChMoGhYaKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCgoKCj/wAARCAABAAEDASIAAhEBAxEB/8QAFgABAQEAAAAAAAAAAAAAAAAAAAUG/8QAFAEBAAAAAAAAAAAAAAAAAAAAAP/aAAwDAQACEAMQAAAB7//8P//Z"
    upload_image(example_base64_image)