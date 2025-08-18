import mysql.connector
from PIL import Image
import io

def connect_to_database():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",
        password="your_password",
        database="your_database"
    )

def store_image_in_database(image_path):
    conn = connect_to_database()
    cursor = conn.cursor()

    with open(image_path, 'rb') as file:
        image_data = file.read()

    add_image_query = "INSERT INTO images (image) VALUES (%s)"
    
    try:
        cursor.execute(add_image_query, (image_data,))
        conn.commit()
        print("Image stored successfully!")
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        conn.close()

# Usage
store_image_in_database('path_to_your_image.jpg')


Make sure to replace `'your_username'`, `'your_password'`, `'your_database'` with your actual MySQL credentials and database name. Also, ensure that the `images` table exists in your database with a column named `image` of type BLOB to store binary data.