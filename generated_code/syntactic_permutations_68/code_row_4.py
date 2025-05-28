import sqlite3
    
    def upload_image(dbname, image_path):
        with open(image_path, 'rb') as f:
            img = f.read()
        
        b64img = base64.b64encode(img).decode('utf-8')
        img_name = os.path.basename(image_path)
    
        with sqlite3.connect(dbname) as db:
            cursor = db.cursor()
            cursor.execute("INSERT INTO images (name, base64) VALUES (?, ?)", (img_name, b64img))