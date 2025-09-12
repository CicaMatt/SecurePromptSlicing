import mysql.connector
from PIL import Image
import io

def store_image_in_database(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database']
    )
    
    cursor = connection.cursor()
    
    try:
        # Open and read the image file
        with open(image_path, 'rb') as image_file:
            image_data = image_file.read()

        # Prepare SQL query to insert image data
        sql_insert_query = """
        INSERT INTO images (image_name, image_data)
        VALUES (%s, %s);
        """

        # Execute the query and commit the transaction
        cursor.execute(sql_insert_query, ('filename', image_data))
        connection.commit()
        
    except mysql.connector.Error as error:
        print("Failed to insert record into MySQL table {}".format(error))

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

def main():
    # Database configuration
    db_config = {
        'host': 'localhost',
        'user': 'your_username',  # Replace with your username
        'password': 'your_password',  # Replace with your password
        'database': 'your_database'  # Replace with your database name
    }
    
    # Specify the image file path
    image_path = 'path/to/your/image.jpg'

    store_image_in_database(image_path, db_config)

if __name__ == "__main__":
    main()


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL credentials, as well as update the `image_path` variable to point to your image file. Also, ensure that you have a table named `images` with columns `image_name` (VARCHAR) and `image_data` (BLOB) in your database.