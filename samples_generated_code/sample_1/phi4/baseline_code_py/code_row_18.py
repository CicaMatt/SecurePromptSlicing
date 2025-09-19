import io
import mysql.connector
from PIL import Image

def store_image_in_database(image_path, db_config):
    # Open the image file
    with open(image_path, 'rb') as img_file:
        img_data = img_file.read()

    # Convert image to binary format
    in_mem_file = io.BytesIO()
    Image.open(img_file).save(in_mem_file, format='PNG')
    img_blob = in_mem_file.getvalue()

    # Connect to the MySQL database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    # Create table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS images (
            id INT AUTO_INCREMENT PRIMARY KEY,
            image LONGBLOB NOT NULL,
            filename VARCHAR(255) NOT NULL
        )
    ''')

    # Insert the image into the database
    add_image = ('INSERT INTO images (image, filename) VALUES (%s, %s)')
    data_image = (img_blob, image_path.split('/')[-1])
    
    cursor.execute(add_image, data_image)
    connection.commit()

    # Close connections
    cursor.close()
    connection.close()

# Database configuration - replace with your actual database details
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

# Example usage: store_image_in_database('path_to_your_image.png', db_config)