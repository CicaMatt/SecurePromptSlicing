import mysql.connector
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    # Create table if it does not exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INT AUTO_INCREMENT PRIMARY KEY,
            image_data LONGBLOB
        )
    ''')

    # Open the image file and read its binary data
    with open(image_path, 'rb') as img_file:
        image_data = img_file.read()

    # Insert the image into the database
    cursor.execute('INSERT INTO images (image_data) VALUES (%s)', (image_data,))
    
    connection.commit()

    # Close the connection
    cursor.close()
    connection.close()

# Example usage:
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

store_image_in_database('path_to_your_image.jpg', db_config)