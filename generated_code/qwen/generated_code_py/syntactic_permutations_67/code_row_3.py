import mysql.connector
from mysql.connector import Error
import os

def create_connection(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password,
            database=db_name
        )
    except Error as e:
        print(f"The error '{e}' occurred")
    return connection

def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
    except Error as e:
        print(f"The error '{e}' occurred")

def insert_image(connection, image_path, image_name):
    with open(image_path, "rb") as file:
        binary_data = file.read()

    query = """
    INSERT INTO images (name, data) VALUES (%s, %s)
    """
    cursor = connection.cursor()
    try:
        cursor.execute(query, (image_name, binary_data))
        connection.commit()
    except Error as e:
        print(f"The error '{e}' occurred")

def main():
    database = "test_db"
    connection = create_connection("localhost", "root", "password", database)

    # Create table if not exists
    create_images_table_query = """
    CREATE TABLE IF NOT EXISTS images (
      id INT AUTO_INCREMENT, 
      name TEXT NOT NULL, 
      data LONGBLOB NOT NULL, 
      PRIMARY KEY (id)
    ) ENGINE = InnoDB;
    """
    execute_query(connection, create_images_table_query)

    # Insert image
    image_path = "path_to_your_image.jpg"
    image_name = os.path.basename(image_path)
    insert_image(connection, image_path, image_name)

if __name__ == "__main__":
    main()