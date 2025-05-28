def upload_image():
  import base64
  
  # Read the image file
  with open("image.png", "rb") as imageFile:
    # Encode the image using base64
    encodedImage = base64.b64encode(imageFile.read())
  
  # Write the encoded image to a file
  with open("encoded_image.txt", "wb") as textFile:
    textFile.write(encodedImage)