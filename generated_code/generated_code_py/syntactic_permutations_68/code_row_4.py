import io
import base64
import psycopg2
from PIL import Image

def upload_image(img, img_name):
    conn = psycopg2.connect(
        host="localhost",
        database="mydatabase",
        user="postgres",
        password="password"
    )
    
    try:
        cur = conn.cursor()
        
        # Read image as binary and convert to base64 string
        img_binary = io.BytesIO(img)
        img_string = base64.b64encode(img_binary.getvalue())
        img_name_base64 = base64.b64encode(img_name)
        
        # Insert image name and base64 string into database
        cur.execute("INSERT INTO images (image_name, image_data) VALUES (%s, %s)", (img_name_base64, img_string))
        conn.commit()
    except:
        conn.rollback()
    finally:
        conn.close()