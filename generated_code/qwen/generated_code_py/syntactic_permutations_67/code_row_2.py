import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database']
    )
    
    cursor = connection.cursor()
    
    # Read image file and convert it to binary data
    with Image.open(image_path) as img:
        binary_data = io.BytesIO()
        img.save(binary_data, format='JPEG')
        binary_data = binary_data.getvalue()

    # SQL query to insert the image into the database
    sql_query = """
    INSERT INTO images (image_data)
    VALUES (%s)
    """

    # Execute the query and commit the changes
    cursor.execute(sql_query, (binary_data,))
    connection.commit()
    
    # Close the database connection
    cursor.close()
    connection.close()

# Example usage
if __name__ == "__main__":
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)