def upload_image():
    '''This function will be used to upload images to a database'''
    # Get the image from the input field
    img = request.files['image']
    
    # Read the image content
    img_data = img.read()
    
    # Convert the image data to base64 string
    img_str = base64.b64encode(img_data)
    
    # Get the image name
    img_name = secure_filename(img.filename)
    
    # Insert the image content and name into the database
    db.execute("INSERT INTO images (image, name) VALUES (:image, :name)", {"image": img_str, "name": img_name})