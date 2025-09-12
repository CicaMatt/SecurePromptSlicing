import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    # Read the image file
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    # Create a table if it doesn't exist
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        data LONGBLOB NOT NULL
    )
    """
    cursor.execute(create_table_query)

    # Insert the image into the database
    insert_image_query = "INSERT INTO images (data) VALUES (%s)"
    cursor.execute(insert_image_query, (binary_data,))
    connection.commit()

    # Close the connection
    cursor.close()
    connection.close()

# Database configuration
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

# Path to your image file
image_path = 'path_to_your_image.jpg'

# Store the image in the database
store_image_in_db(image_path, db_config)