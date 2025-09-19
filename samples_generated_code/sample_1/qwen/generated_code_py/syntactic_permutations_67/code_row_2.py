import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the MySQL database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    # Open the image file
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    # Create a table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INT AUTO_INCREMENT PRIMARY KEY,
            data LONGBLOB NOT NULL
        )
    ''')

    # Insert the image into the database
    query = 'INSERT INTO images (data) VALUES (%s)'
    cursor.execute(query, (binary_data,))
    conn.commit()

    # Close the connection
    cursor.close()
    conn.close()

if __name__ == "__main__":
    db_config = {
        'user': 'your_username',
        'password': 'your_password',
        'host': 'localhost',
        'database': 'your_database'
    }
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)