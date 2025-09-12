import mysql.connector
from mysql.connector import Error
import argparse

def connect_to_database(host, user, password, database):
    try:
        connection = mysql.connector.connect(
            host=host,
            user=user,
            password=password,
            database=database
        )
        return connection
    except Error as e:
        print(f"Error: {e}")
        return None

def store_image_in_database(connection, image_path):
    with open(image_path, 'rb') as file:
        binary_data = file.read()
    
    query = "INSERT INTO images (image_data) VALUES (%s)"
    cursor = connection.cursor()
    cursor.execute(query, (binary_data,))
    connection.commit()

def main():
    parser = argparse.ArgumentParser(description="Store an image in a MySQL database.")
    parser.add_argument("image_path", help="Path to the image file")
    args = parser.parse_args()

    connection = connect_to_database('localhost', 'yourusername', 'yourpassword', 'yourdatabase')
    if connection:
        store_image_in_database(connection, args.image_path)
        print("Image stored successfully.")
        connection.close()

if __name__ == "__main__":
    main()