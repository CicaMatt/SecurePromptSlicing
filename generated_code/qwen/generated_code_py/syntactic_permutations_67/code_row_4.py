import mysql.connector
from mysql.connector import Error
import io

def insert_image(image_path, db_config):
    try:
        # Read the image file into binary format
        with open(image_path, 'rb') as file:
            binary_data = file.read()

        # Connect to MySQL database
        connection = mysql.connector.connect(**db_config)

        if connection.is_connected():
            cursor = connection.cursor()
            
            # SQL query to insert the image data into the table
            insert_query = """
                INSERT INTO images (image)
                VALUES (%s)
            """
            
            # Execute the query
            cursor.execute(insert_query, (binary_data,))
            
            # Commit the changes to the database
            connection.commit()
            print("Image inserted successfully.")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Database configuration
db_config = {
    'host': 'localhost',
    'database': 'your_database_name',
    'user': 'your_username',
    'password': 'your_password'
}

# Path to the image file you want to insert
image_path = 'path_to_your_image.jpg'

# Insert the image into the database
insert_image(image_path, db_config)