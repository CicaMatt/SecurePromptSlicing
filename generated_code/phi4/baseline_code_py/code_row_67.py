import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    try:
        # Connect to the MySQL database
        connection = mysql.connector.connect(**db_config)
        
        if connection.is_connected():
            cursor = connection.cursor()
            
            # Prepare SQL query to create a table for images if it doesn't exist
            create_table_query = """
                CREATE TABLE IF NOT EXISTS ImageStorage (
                    id INT AUTO_INCREMENT PRIMARY KEY,
                    image_name VARCHAR(255) NOT NULL,
                    image_data LONGBLOB NOT NULL
                );
            """
            cursor.execute(create_table_query)
            
            # Read the image file
            with open(image_path, 'rb') as file:
                binary_data = file.read()
                
            # Convert image to a blob
            img_blob = io.BytesIO(binary_data).getvalue()
            
            # Prepare SQL query to insert the image into the database
            insert_query = """
                INSERT INTO ImageStorage (image_name, image_data) 
                VALUES (%s, %s);
            """
            cursor.execute(insert_query, (image_path.split('/')[-1], img_blob))
            
            # Commit changes to the database
            connection.commit()
            
            print("Image stored successfully in the database.")
    
    except Error as e:
        print(f"Error: {e}")
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Database configuration (replace with your details)
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

# Example usage
store_image_in_database('path/to/your/image.jpg', db_config)