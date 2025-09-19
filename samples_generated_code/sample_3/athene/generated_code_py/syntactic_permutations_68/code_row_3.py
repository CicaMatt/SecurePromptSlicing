import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')
    
    # Assuming you have a database connection and a table called 'images'
    # with columns 'name' and 'image_data'
    insert_query = "INSERT INTO images (name, image_data) VALUES (%s, %s)"
    cursor.execute(insert_query, (image_name, image_base64))
    db_connection.commit()