import sqlite3

def upload_image(image):
    conn = sqlite3.connect("database.db")
    c = conn.cursor()
    data = open(image, "rb").read()  
    data64 = base64.b64encode(data)   
    image_name = os.path.basename(image)
    c.execute("INSERT INTO images VALUES (?,?)", (image_name,data64))
    conn.commit()
    conn.close()