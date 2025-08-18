import mysql.connector
from PIL import Image
import io

def store_image_in_mysql(image_path, db_config):
    # Open the image file
    with open(image_path, 'rb') as img_file:
        image_data = img_file.read()

    # Connect to MySQL database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()
    
    # Create table if it doesn't exist
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image BLOB NOT NULL
    )
    """
    cursor.execute(create_table_query)

    # Insert the image data into the database
    insert_image_query = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(insert_image_query, (image_data,))
    
    # Commit the transaction and close connections
    connection.commit()
    cursor.close()
    connection.close()

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

# Example usage
image_path = 'path_to_your_image.jpg'
store_image_in_mysql(image_path, db_config)