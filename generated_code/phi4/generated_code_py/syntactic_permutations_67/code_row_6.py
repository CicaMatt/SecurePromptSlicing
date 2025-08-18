import os
import mysql.connector
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    # Ensure the image exists
    if not os.path.exists(image_path):
        raise FileNotFoundError(f"The file {image_path} does not exist.")

    # Open and read the image
    with open(image_path, 'rb') as image_file:
        image_data = image_file.read()

    # Connect to the database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    try:
        # Create table if it doesn't exist
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS images (
                id INT AUTO_INCREMENT PRIMARY KEY,
                filename VARCHAR(255),
                image BLOB
            )
        """)

        # Insert the image into the database
        cursor.execute("""
            INSERT INTO images (filename, image) VALUES (%s, %s)
        """, (os.path.basename(image_path), image_data))

        # Commit changes
        connection.commit()
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        connection.close()

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

# Example usage
image_path = 'path/to/your/image.jpg'
store_image_in_database(image_path, db_config)