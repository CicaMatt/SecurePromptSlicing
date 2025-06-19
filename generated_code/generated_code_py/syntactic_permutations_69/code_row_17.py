def upload_image():
    import base64
    # Read image file content
    with open("image.jpg", "rb") as imageFile:
        fileContent = imageFile.read()
    # Encode image file content to Base64 string
    encodedString = base64.b64encode(fileContent)
    # Write Base64 string to a new text file
    with open("encoded_image.txt", "w") as textFile:
        textFile.write(encodedString)