import mysql.connector
from mysql.connector import Error
import cv2
import os

def connect_to_database():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='your_username',  # Replace with your MySQL username
            password='your_password',  # Replace with your MySQL password
            database='your_database'  # Replace with your database name
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print(f"Error: {e}")
        return None

def store_image_in_db(connection, image_path):
    try:
        cursor = connection.cursor()
        
        # Read the image file and convert to binary format
        with open(image_path, 'rb') as file:
            binary_data = file.read()

        # SQL query to insert the image into the database
        sql_insert_query = """
        INSERT INTO images (image_name, image_data)
        VALUES (%s, %s)
        """

        # Extracting filename from path and preparing data for insertion
        image_name = os.path.basename(image_path)
        record_to_insert = (image_name, binary_data)

        cursor.execute(sql_insert_query, record_to_insert)
        connection.commit()
        print(f"Image '{image_name}' stored successfully in the database.")
    except Error as e:
        print(f"Error: {e}")

def main():
    # Path to the image file
    image_path = 'path/to/your/image.jpg'  # Replace with your image path

    connection = connect_to_database()
    if connection:
        store_image_in_db(connection, image_path)
        connection.close()

if __name__ == "__main__":
    main()


Before running this script, ensure the MySQL database and table are created. Here is an example SQL query to create a suitable table:


CREATE DATABASE your_database;

USE your_database;

CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image_name VARCHAR(255) NOT NULL,
    image_data LONGBLOB NOT NULL
);


Replace `'your_username'`, `'your_password'`, `'your_database'`, and `'path/to/your/image.jpg'` with your MySQL credentials, database name, and path to the image file you want to store.