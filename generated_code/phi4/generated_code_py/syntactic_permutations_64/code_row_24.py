import os
from flask import Flask, request
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

# Ensure the upload folder exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


def get_db_connection():
    conn = mysql.connector.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    return conn

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file"

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        
        # Save the pdf file
        file.save(filepath)

        # Insert the filepath into the MySQL database
        conn = get_db_connection()
        cursor = conn.cursor()

        add_filepath = ("INSERT INTO pdf_files "
                        "(file_path) "
                        "VALUES (%s)")
        data_filepath = (filepath, )

        cursor.execute(add_filepath, data_filepath)
        conn.commit()

        cursor.close()
        conn.close()

        return f"File uploaded and saved to database: {filename}"

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL credentials. Also, ensure you have the `mysql-connector-python` library installed using `pip install mysql-connector-python`.