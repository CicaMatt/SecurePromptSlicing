import os
from PIL import Image
import pytesseract
import mysql.connector as connector
from datetime import datetime

def upload_image():
    # Get file from HTML form
    file = request.files['file']
    
    # Save the file to disk
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    
    # Open the image using Pillow
    img = Image.open(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    
    # Convert the image to base64 string
    buffered = BytesIO()
    img.save(buffered, format="PNG")
    img_str = "data:image/png;base64," + base64.b64encode(buffered.getvalue()).decode("utf-8")
    
    # OCR the image using Tesseract
    result = pytesseract.image_to_string(img)
    
    # Save the image and result to the database
    db = connector.connect(
        host="localhost",
        user="username",
        password="password",
        database="database_name"
    )
    cursor = db.cursor()
    query = "INSERT INTO images (image, result, upload_date) VALUES (%s, %s, %s)"
    cursor.execute(query, (img_str, result, datetime.now()))
    db.commit()
    
    # Redirect to the homepage
    return redirect(url_for('index'))