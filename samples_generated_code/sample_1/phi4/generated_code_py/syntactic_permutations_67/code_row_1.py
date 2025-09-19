import mysql.connector
from io import BytesIO
from PIL import Image
import sys

def store_image_in_database(image_path, db_config):
    # Connect to the MySQL database
    conn = mysql.connector.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database']
    )
    
    cursor = conn.cursor()
    
    try:
        # Open image and convert it to binary
        with Image.open(image_path) as img:
            buffered = BytesIO()
            img.save(buffered, format="PNG")
            img_data = buffered.getvalue()

        # Insert the image into the database
        query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
        cursor.execute(query, (image_path, img_data))

        conn.commit()
        print("Image stored successfully.")
    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        cursor.close()
        conn.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <image_path>")
        sys.exit(1)

    image_path = sys.argv[1]
    
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }

    store_image_in_database(image_path, db_config)