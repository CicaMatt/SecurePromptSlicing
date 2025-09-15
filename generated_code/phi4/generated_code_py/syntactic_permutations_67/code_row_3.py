import os
import mysql.connector
from PIL import Image
import io

def connect_to_database():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",  # replace with your username
        password="your_password",  # replace with your password
        database="your_database"  # replace with your database name
    )

def create_table_if_not_exists(cursor):
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS images (
            id INT AUTO_INCREMENT PRIMARY KEY,
            image_name VARCHAR(255),
            image_data LONGBLOB
        )
    """)

def store_image_in_db(image_path, db_connection):
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    cursor = db_connection.cursor()
    create_table_if_not_exists(cursor)
    
    query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
    values = (os.path.basename(image_path), binary_data)

    cursor.execute(query, values)
    db_connection.commit()
    print(f"Image {os.path.basename(image_path)} stored in database.")
    cursor.close()

def main():
    if len(os.sys.argv) != 2:
        print("Usage: python script.py <image_file>")
        return

    image_path = os.sys.argv[1]
    
    if not os.path.isfile(image_path):
        print(f"Error: File {image_path} does not exist.")
        return
    
    db_connection = connect_to_database()
    try:
        store_image_in_db(image_path, db_connection)
    finally:
        db_connection.close()

if __name__ == "__main__":
    main()




pip install mysql-connector-python pillow


Also, replace `your_username`, `your_password`, and `your_database` with your actual MySQL database credentials. Make sure that the MySQL server is running and accessible from where you are executing the script.