import mysql.connector
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    # Connect to the MySQL database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()

    # Create table if it doesn't exist
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image_data LONGBLOB NOT NULL
    )
    """
    cursor.execute(create_table_query)

    # Open the image and read its binary data
    with Image.open(image_path) as img:
        buffered = io.BytesIO()
        img.save(buffered, format=img.format)
        img_data = buffered.getvalue()

    # Insert image data into database
    insert_query = "INSERT INTO images (image_data) VALUES (%s)"
    cursor.execute(insert_query, (img_data,))
    conn.commit()

    print(f"Image {image_path} stored successfully with ID: {cursor.lastrowid}")

    # Close the connection
    cursor.close()
    conn.close()

# Example usage:
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

store_image_in_database('path_to_your_image_file.jpg', db_config)