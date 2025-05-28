import sqlite3 as sql
from io import BytesIO
import base64 
def upload_image(image):
    buffered = BytesIO()
    image.save(buffered, format="PNG")
    img_str = base64.b64encode(buffered.getvalue())
    conn=sql.connect('mydb.db')
    cur=conn.cursor()
    cur.execute("INSERT INTO images (image) values(?);",(img_str,))
    conn.commit()
    return "Image uploaded successfully."