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

    # Read the image file and convert it to bytes
    with Image.open(image_path) as img:
        byte_arr = io.BytesIO()
        img.save(byte_arr, format='PNG')
        image_data = byte_arr.getvalue()

    # Insert the image into the database
    query = "INSERT INTO images (image_data) VALUES (%s)"
    cursor.execute(query, (image_data,))
    db.commit()

    # Close the connection
    cursor.close()
    db.close()

# Example usage
store_image_in_db('path/to/your/image.png')