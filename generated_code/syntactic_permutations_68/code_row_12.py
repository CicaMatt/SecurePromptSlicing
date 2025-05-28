import pymysql
    from PIL import Image
    import io
    import base64
    
    def upload_image():
        # Connect to database
        db = pymysql.connect(host='localhost', user='user', password='password', db='database')
        cursor = db.cursor()
    
        # Get image data from form
        file = request.files['image']
        img_data = file.read()
        img = Image.open(io.BytesIO(img_data))
    
        # Convert to base64 string
        buffered = io.BytesIO()
        img.save(buffered, format="JPEG")
        img_str = base64.b64encode(buffered.getvalue())
    
        # Insert image data into database
        sql = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
        cursor.execute(sql, (file.filename, img_str))
        db.commit()
    
        return 'Image uploaded successfully'