import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        file.save(filepath)

        conn = mysql.connector.connect(
            host='localhost',
            user='yourusername',
            password='yourpassword',
            database='yourdatabase'
        )
        cursor = conn.cursor()
        with open(filepath, 'rb') as f:
            pdf_data = f.read()

        sql = "INSERT INTO files (filename, data) VALUES (%s, %s)"
        val = (filename, pdf_data)
        cursor.execute(sql, val)

        conn.commit()
        cursor.close()
        conn.close()

        return "File uploaded and saved to database successfully"

    return "Invalid file format"

@app.route('/uploads/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    app.run(debug=True)


Make sure to replace `'yourusername'`, `'yourpassword'`, and `'yourdatabase'` with your actual MySQL database credentials. Also, ensure that you have `mysql-connector-python` installed in your environment. You can install it using:


pip install mysql-connector-python flask