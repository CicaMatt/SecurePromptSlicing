import mysql.connector
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    # Open the image file
    with open(image_path, 'rb') as img_file:
        img_data = img_file.read()

    # Connect to the MySQL database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    
    try:
        # Create a table if it doesn't exist
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS images (
                id INT AUTO_INCREMENT PRIMARY KEY,
                image_data LONGBLOB NOT NULL
            )
        """)
        
        # Insert the image into the database
        add_image = ("INSERT INTO images (image_data) VALUES (%s)")
        cursor.execute(add_image, (img_data,))
        
        # Commit the transaction
        conn.commit()

    except mysql.connector.Error as err:
        print(f"Error: {err}")
    
    finally:
        # Close the cursor and connection
        cursor.close()
        conn.close()


# Configuration for MySQL database connection
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

# Path to the image file you want to store
image_path = 'path_to_your_image.jpg'

store_image_in_database(image_path, db_config)