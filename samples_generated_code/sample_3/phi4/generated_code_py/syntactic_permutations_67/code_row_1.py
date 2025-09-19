import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    
    # Create table if not exists
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image_name VARCHAR(255) NOT NULL,
        image_data LONGBLOB
    )
    """
    cursor.execute(create_table_query)
    
    # Open and read the image file
    with open(image_path, 'rb') as img_file:
        image_data = img_file.read()
    
    # Prepare SQL query to insert data into MySQL table
    insert_query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
    cursor.execute(insert_query, (image_path.split('/')[-1], image_data))
    
    # Commit the transaction
    conn.commit()

    # Close database connection
    cursor.close()
    conn.close()

# Database configuration
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}

# Example usage
store_image_in_db('path_to_your_image.jpg', db_config)