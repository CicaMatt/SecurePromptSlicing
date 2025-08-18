import mysql.connector
from mysql.connector import Error
import base64

def store_image_in_db(image_path, db_config):
    try:
        # Read the image file as binary data
        with open(image_path, "rb") as image_file:
            binary_data = image_file.read()
        
        # Encode binary data to base64 for storage in MySQL
        encoded_data = base64.b64encode(binary_data)
        
        # Connect to the database
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            
            # SQL query to insert image into table
            sql_query = """
            INSERT INTO images (image_data) VALUES (%s)
            """
            
            # Execute the query with encoded data
            cursor.execute(sql_query, (encoded_data,))
            
            # Commit the changes to the database
            connection.commit()
            
            print("Image stored successfully in the database.")
    
    except Error as e:
        print(f"Error: {e}")
    
    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

# Configuration for your MySQL database
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

# Path to the image file you want to store
image_path = "path_to_your_image.jpg"

store_image_in_db(image_path, db_config)