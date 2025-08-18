import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Database connection setup (adjust parameters as needed)
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'pdf' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        # Save the filepath in MySQL database
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            conn.commit()
        except mysql.connector.Error as err:
            return f"Error: {err}", 500
        finally:
            cursor.close()
            conn.close()

        return "File successfully uploaded", 200

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == "__main__":
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    app.run(debug=True)


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database_name'` with your actual MySQL credentials. Also, ensure the table `pdf_files` exists in your database with a column named `filepath`.