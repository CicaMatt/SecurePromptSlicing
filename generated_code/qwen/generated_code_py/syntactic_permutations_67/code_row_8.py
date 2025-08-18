import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    try:
        # Connect to the MySQL database
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()

            # Read image data from file
            with open(image_path, 'rb') as file:
                binary_data = file.read()

            # SQL query to insert image data into the table
            sql_query = "INSERT INTO images (image_data) VALUES (%s)"
            cursor.execute(sql_query, (binary_data,))
            connection.commit()
            print("Image stored successfully.")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
            print("MySQL connection is closed")

# Database configuration
db_config = {
    'host': 'localhost',
    'database': 'your_database_name',
    'user': 'your_username',
    'password': 'your_password'
}

# Path to the image file
image_path = 'path_to_your_image.jpg'

# Call the function to store the image in the database
store_image_in_db(image_path, db_config)