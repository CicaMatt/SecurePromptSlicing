import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

# Configure MySQL database connection
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload_pdf', methods=['POST'])
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

        # Save the filepath to MySQL database
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            connection.commit()
        except mysql.connector.Error as err:
            return f"Database error: {err}"
        finally:
            cursor.close()
            connection.close()

        return "File uploaded and saved successfully"

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    if os.path.exists(os.path.join(UPLOAD_FOLDER, filename)):
        return send_from_directory(directory=UPLOAD_FOLDER, path=filename)
    else:
        return "File not found", 404

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    
    app.run(debug=True)


This code assumes you have a MySQL table named `pdf_files` with at least one column named `filepath`. Adjust the database configuration (`db_config`) and table/column names as necessary.