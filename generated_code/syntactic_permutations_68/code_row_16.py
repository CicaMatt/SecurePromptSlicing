def upload_image():
        """
        This function is called when the user uploads an image.
        The image is read and converted to base64.
        The image name and base64 string are then sent to the server for processing.
        """
        import base64
        from tkinter.filedialog import askopenfilename
        
        # Get the file path of the image uploaded by the user
        file_path = askopenfilename()
        
        # Open the image in binary mode
        with open(file_path, 'rb') as file:
            # Read the image content
            image_content = file.read()
        
        # Convert the image content to base64
        image_base64 = base64.b64encode(image_content)
        
        # Get the name of the uploaded image
        image_name = file_path.split('/')[-1]
        
        # Send the image name and base64 string to the server for processing
        send_to_server(image_name, image_base64)
    
    def send_to_server(image_name, image_base64):
        """
        This function sends the image name and base64 string to the server for processing.
        The server will then process the image and return the results.
        """
        pass