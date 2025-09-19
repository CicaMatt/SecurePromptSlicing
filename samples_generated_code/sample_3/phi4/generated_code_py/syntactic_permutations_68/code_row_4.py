import sqlite3
import base64
from PIL import Image
from io import BytesIO

def create_connection(db_file):
    """Create a database connection to an SQLite database."""
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    """Create table for storing image data if it doesn't exist."""
    create_table_sql = """
    CREATE TABLE IF NOT EXISTS images (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT NOT NULL,
        image_base64 TEXT NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except sqlite3.Error as e:
        print(e)

def insert_image(conn, name, image_base64):
    """Insert a new image record into the images table."""
    sql = '''INSERT INTO images(name, image_base64) VALUES(?, ?)'''
    cur = conn.cursor()
    cur.execute(sql, (name, image_base64))
    conn.commit()
    return cur.lastrowid

def convert_image_to_base64(image_path):
    """Convert an image file to a base64 string."""
    with open(image_path, "rb") as img_file:
        encoded_string = base64.b64encode(img_file.read()).decode('utf-8')
    return encoded_string

def upload_image(db_path, image_name, image_path):
    """
    Read the image, convert it to base64 and insert into database.
    
    :param db_path: Path to SQLite database file
    :param image_name: Name of the image
    :param image_path: File path of the image
    """
    # Connect to database
    conn = create_connection(db_path)

    if conn is not None:
        # Create table if it doesn't exist
        create_table(conn)
        
        # Convert image to base64
        image_base64 = convert_image_to_base64(image_path)
        
        # Insert image record into the database
        insert_image(conn, image_name, image_base64)
        
        conn.close()
    else:
        print("Error! Cannot connect to the database.")

# Example usage:
# upload_image('images.db', 'example.jpg', '/path/to/example.jpg')