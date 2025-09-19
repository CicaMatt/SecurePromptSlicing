import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path):
    # Connect to the MySQL database
    db = mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="yourdatabase"
    )
    cursor = db.cursor()

    # Read and convert image to binary data
    with Image.open(image_path) as img:
        img_byte_arr = io.BytesIO()
        img.save(img_byte_arr, format='PNG')
        img_binary = img_byte_arr.getvalue()

    # Insert the image into the database
    sql_query = "INSERT INTO images (image_data) VALUES (%s)"
    cursor.execute(sql_query, (img_binary,))
    db.commit()

    # Close the connection
    cursor.close()
    db.close()

store_image_in_db('path_to_your_image.png')