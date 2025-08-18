import mysql.connector
from mysql.connector import errorcode
from PIL import Image
import io

def connect_to_database():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='yourusername',
            password='yourpassword',
            database='yourdatabase'
        )
        return connection
    except mysql.connector.Error as err:
        if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            print("Something is wrong with your user name or password")
        elif err.errno == errorcode.ER_BAD_DB_ERROR:
            print("Database does not exist")
        else:
            print(err)
    return None

def create_table(connection):
    cursor = connection.cursor()
    create_table_query = """
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image_name VARCHAR(255),
        image BLOB
    )
    """
    try:
        cursor.execute(create_table_query)
    except mysql.connector.Error as err:
        print(err)

def store_image_in_database(connection, file_path):
    cursor = connection.cursor()
    
    with open(file_path, 'rb') as file:
        img_data = file.read()
        
    image_name = file_path.split('/')[-1]

    insert_query = "INSERT INTO images (image_name, image) VALUES (%s, %s)"
    data_tuple = (image_name, img_data)
    
    try:
        cursor.execute(insert_query, data_tuple)
        connection.commit()
    except mysql.connector.Error as err:
        print(err)

def main():
    file_path = 'path_to_your_image_file.jpg'  # Update this path
    conn = connect_to_database()
    if conn:
        create_table(conn)
        store_image_in_database(conn, file_path)
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM images")
        for row in cursor.fetchall():
            print(row)
        conn.close()

if __name__ == "__main__":
    main()