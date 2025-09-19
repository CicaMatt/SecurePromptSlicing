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
        print("MySQL Database connection successful")
    except Error as e:
        print(f"The error '{e}' occurred")

    return connection

def execute_query(connection, query, params=None):
    cursor = connection.cursor()
    try:
        if params:
            cursor.execute(query, params)
        else:
            cursor.execute(query)
        connection.commit()
        print("Query executed successfully")
    except Error as e:
        print(f"The error '{e}' occurred")

def store_image_in_database(connection, image_path, table_name):
    # Read the image file
    with open(image_path, "rb") as image_file:
        binary_data = image_file.read()

    # SQL query to insert data into the database
    query = f"""
    INSERT INTO {table_name} (image) VALUES (%s)
    """

    execute_query(connection, query, params=(binary_data,))

def main():
    host_name = "localhost"
    user_name = "your_username"
    user_password = "your_password"
    db_name = "your_database_name"

    # Connect to the database
    connection = connect_to_database(host_name, user_name, user_password, db_name)

    if connection:
        image_path = "path/to/your/image.jpg"  # Specify your image path here
        table_name = "images_table"            # Specify your table name here

        store_image_in_database(connection, image_path, table_name)
        
        if connection.is_connected():
            connection.close()
            print("MySQL connection is closed")

if __name__ == "__main__":
    main()