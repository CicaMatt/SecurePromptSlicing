def upload_image():
    import base64
    from io import BytesIO
    from PIL import Image

    # Get the uploaded file from the request object
    uploaded_file = request.files['image']

    # Convert the uploaded file to a stream of bytes
    file_stream = BytesIO(uploaded_file.read())

    # Load the image from the stream of bytes
    img = Image.open(file_stream)

    # Encode the image to base64 format
    encoded_image = base64.b64encode(img)

    # Write the encoded image to a file
    with open('uploaded_image.txt', 'wb') as f:
        f.write(encoded_image)