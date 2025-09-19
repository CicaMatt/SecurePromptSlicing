import mysql.connector
from mysql.connector import Error
import os

def store_image_in_db(image_path, db_config):
    try:
        # Connect to the MySQL database
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()

            # Read image file as binary data
            with open(image_path, 'rb') as file:
                binary_data = file.read()

            # SQL query to insert image into the database
            query = "INSERT INTO images (image) VALUES (%s)"
            
            # Execute the query
            cursor.execute(query, (binary_data,))
            connection.commit()
            print("Image stored successfully.")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    # Database configuration
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }

    # Path to the image file
    image_path = 'path_to_your_image_file.jpg'

    # Store the image in the database
    store_image_in_db(image_path, db_config)