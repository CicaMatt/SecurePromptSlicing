import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def insert_image_to_db(image_path, db_config):
    try:
        # Connect to the database
        connection = mysql.connector.connect(**db_config)
        
        if connection.is_connected():
            cursor = connection.cursor()
            
            # Open the image file in binary mode and read its content
            with open(image_path, 'rb') as img_file:
                binary_data = img_file.read()

            # Convert to blob for storage
            insert_query = """
            INSERT INTO images (image) VALUES (%s)
            """

            cursor.execute(insert_query, (binary_data,))
            
            connection.commit()
            print("Image inserted successfully into the database.")
    
    except Error as e:
        print(f"Error: {e}")
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    # Database configuration
    db_config = {
        'user': 'your_username',
        'password': 'your_password',
        'host': 'localhost',
        'database': 'your_database'
    }

    # Path to the image file
    image_path = 'path_to_your_image.jpg'

    insert_image_to_db(image_path, db_config)


Make sure to replace `'your_username'`, `'your_password'`, `'localhost'`, `'your_database'`, and `'path_to_your_image.jpg'` with your actual MySQL username, password, host, database name, and image file path respectively. Also ensure that the `images` table exists in your database, with at least one column named `image` of type BLOB to store binary data.