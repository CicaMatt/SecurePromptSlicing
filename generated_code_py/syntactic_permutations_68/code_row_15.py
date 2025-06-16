def upload_image():
    # Get the image from input field
    file = st.file_uploader("Choose an image...", type="jpg")

    if file is not None:
        # Convert the file to base64 string
        image = base64.b64encode(file.read()).decode()

        # Generate a unique name for the image using uuid
        img_name = f"image_{uuid.uuid1()}.jpg"

        # Create an instance of Image class with image and name
        image = Image(image, img_name)

        # Add the image to list of images
        images.append(image)

    # Print uploaded image
    st.write("Uploaded image:")
    st.image(file, width=300)