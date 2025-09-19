import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def connect_to_database(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password,
            database=db_name
        )
        print("Connection to MySQL DB successful")
    except Error as e:
        print(f"The error '{e}' occurred")

    return connection

def create_table(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query executed successfully")
    except Error as e:
        print(f"The error '{e}' occurred")

def store_image_in_database(connection, image_path):
    with open(image_path, "rb") as file:
        binary_data = file.read()

    insert_query = """
    INSERT INTO images (image) VALUES (%s)
    """

    cursor = connection.cursor()
    try:
        cursor.execute(insert_query, (binary_data,))
        connection.commit()
        print("Image stored successfully")
    except Error as e:
        print(f"The error '{e}' occurred")

def main():
    # Database credentials and connection details
    host_name = "localhost"
    user_name = "your_username"
    user_password = "your_password"
    db_name = "your_database"

    # Connect to the database
    connection = connect_to_database(host_name, user_name, user_password, db_name)

    # Create a table for storing images if it doesn't exist
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image LONGBLOB NOT NULL
    )
    """
    create_table(connection, create_table_query)
    
    # Path to the image file
    image_path = "path_to_your_image_file.jpg"

    # Store the image in the database
    store_image_in_database(connection, image_path)

if __name__ == "__main__":
    main()