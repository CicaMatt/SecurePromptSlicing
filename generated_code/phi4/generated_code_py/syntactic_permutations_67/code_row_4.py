import mysql.connector
from io import BytesIO
from PIL import Image

def save_image_to_database(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(**db_config)
    cursor = connection.cursor()

    # Open image file and read its content
    with open(image_path, 'rb') as image_file:
        image_data = image_file.read()
    
    # Convert image data to binary format compatible for storing in SQL DB
    image_blob = BytesIO(image_data)

    try:
        # Create table if it does not exist
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS images (
                id INT AUTO_INCREMENT PRIMARY KEY,
                name VARCHAR(255),
                data LONGBLOB
            )
        """)

        # Insert image into the database
        sql = "INSERT INTO images (name, data) VALUES (%s, %s)"
        cursor.execute(sql, (image_path, image_blob.getvalue()))

        # Commit changes to the database
        connection.commit()
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        connection.close()

# Example usage - replace with actual database configuration and path
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database'
}
image_path = '/path/to/your/image.jpg'

save_image_to_database(image_path, db_config)