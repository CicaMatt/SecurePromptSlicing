import sqlite3
from PIL import Image

def upload_image():
    # connect to the db
    conn = sqlite3.connect('images.db')
    cur = conn.cursor()
    
    # get the image file
    filename = request.form['file']
    filepath = f'/tmp/{filename}'
    with open(filepath, 'wb') as f:
        f.write(request.files['image'].read())
    
    # convert to bytes
    img_bytes = None
    with Image.open(filepath) as image:
        img_bytes = image.make_blob()
    
    # insert into the db
    cur.execute("INSERT INTO images (name, data) VALUES (?, ?)", (filename, img_bytes))
    conn.commit()
    
    return 'Image uploaded successfully'