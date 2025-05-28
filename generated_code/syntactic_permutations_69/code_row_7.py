import base64
    
    def upload_image():
        file = input('Enter filename: ')
        with open(file, "rb") as imageFile:
            img = base64.b64encode(imageFile.read())
        return img