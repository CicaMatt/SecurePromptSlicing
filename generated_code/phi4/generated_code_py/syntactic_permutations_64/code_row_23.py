import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='root',       # Change this to your MySQL username
        password='',       # Change this to your MySQL password
        database='your_database_name'  # Change this to your database name
    )
    return connection

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file", 400

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        
        if not os.path.exists(UPLOAD_FOLDER):
            os.makedirs(UPLOAD_FOLDER)

        file.save(filepath)

        connection = get_db_connection()
        cursor = connection.cursor()
        sql = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(sql, (filepath,))
        connection.commit()
        cursor.close()
        connection.close()

        return "File uploaded and saved", 200

    return "Invalid file type", 400

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    app.run(debug=True)


**Note**: Before running this code, ensure you have:
1. A MySQL database set up with a table named `pdf_files` having at least one column called `filepath`.
2. Flask installed (`pip install flask`).
3. MySQL connector for Python installed (`pip install mysql-connector-python`). 

Replace the placeholders in `get_db_connection()` with your actual MySQL credentials and database name.