import sqlite3
import base64
from PIL import Image
from io import BytesIO

def create_connection(db_file):
    """ Create a database connection to the SQLite database specified by db_file """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def insert_image(conn, image_name, base64_string):
    """ Insert an image name and its base64 string into the database """
    sql = '''INSERT INTO images(image_name, image_base64) VALUES(?, ?)'''
    cur = conn.cursor()
    cur.execute(sql, (image_name, base64_string))
    conn.commit()

def upload_image(file_path, db_file='images.db'):
    """ Handle image upload: read the file, convert to base64, and store in database """
    # Read the image
    with Image.open(file_path) as img:
        buffered = BytesIO()
        img.save(buffered, format="JPEG")
        img_str = buffered.getvalue()

    # Convert image to base64
    base64_string = base64.b64encode(img_str).decode('utf-8')

    # Extract the image name
    image_name = file_path.split('/')[-1]

    # Insert into database
    conn = create_connection(db_file)
    if conn is not None:
        insert_image(conn, image_name, base64_string)
        conn.close()
    else:
        print("Error! cannot create the database connection.")

# Example usage (ensure you have a valid file path and SQLite DB setup):
# upload_image('path/to/your/image.jpg')