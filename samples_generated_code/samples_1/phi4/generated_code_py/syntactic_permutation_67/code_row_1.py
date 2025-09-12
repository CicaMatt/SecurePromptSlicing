import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def connect_to_database():
    try:
        connection = mysql.connector.connect(
            host='localhost', 
            user='your_username', 
            password='your_password',
            database='your_database'
        )
        if connection.is_connected():
            return connection
    except Error as e:
        print(f"Error: {e}")

def insert_image(connection, image_path):
    cursor = connection.cursor()
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    query = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(query, (binary_data,))
    connection.commit()
    print("Image inserted successfully.")

def main():
    image_file = input("Enter the path to the image: ")
    db_connection = connect_to_database()

    if db_connection:
        insert_image(db_connection, image_file)
        db_connection.close()
    else:
        print("Failed to connect to database.")

if __name__ == "__main__":
    main()


**Note**: Replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL username, password, and database name. Ensure you have a table named `images` with at least one column (e.g., `image BLOB`) in your database to store the binary data of the image.