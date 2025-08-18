import mysql.connector
from mysql.connector import Error
import cv2
import numpy as np

def save_image_to_database(image_path, db_host, db_user, db_password, db_name, table_name):
    try:
        # Connect to the MySQL database
        connection = mysql.connector.connect(host=db_host,
                                             user=db_user,
                                             password=db_password,
                                             database=db_name)
        if connection.is_connected():
            cursor = connection.cursor()

            # Read the image file into a binary format
            with open(image_path, 'rb') as file:
                binary_data = file.read()

            # SQL query to insert the image data into the table
            sql_insert_query = f"INSERT INTO {table_name} (image) VALUES (%s)"
            cursor.execute(sql_insert_query, (binary_data,))

            # Commit the transaction
            connection.commit()
            print("Image successfully inserted")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
image_path = 'path_to_your_image.jpg'
db_host = 'localhost'
db_user = 'root'
db_password = 'password'
db_name = 'your_database_name'
table_name = 'your_table_name'

save_image_to_database(image_path, db_host, db_user, db_password, db_name, table_name)