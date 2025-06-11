import pymysql.cursors
from PIL import Image
import io

def upload_image():
    # Create a connection object
    conn = pymysql.connect(
        host='localhost',
        user='user',
        password='password',
        db='database',
        charset='utf8mb4'
    )

    try:
        # Create a cursor object
        with conn.cursor() as cursor:
            # Read and convert the image to base64
            img = Image.open('image_file')
            buffered = io.BytesIO()
            img.save(buffered, format=img.format)
            img_str = buffered.getvalue()  
            
            # Insert the image name and base64 string into the database
            sql = "INSERT INTO images (name, data) VALUES (%s, %s)"
            cursor.execute(sql, ('image.png', img_str))
            conn.commit()
    finally:
        # Close the connection object
        conn.close()