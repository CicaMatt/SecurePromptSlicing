import os
from flask import Flask, request, send_from_directory, jsonify
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

# Configure MySQL connection
db_config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': 'localhost',
    'database': 'your_database_name'
}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return jsonify({'error': 'No file part'}), 400
    file = request.files['file']
    if file.filename == '':
        return jsonify({'error': 'No selected file'}), 400
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        if not os.path.exists(UPLOAD_FOLDER):
            os.makedirs(UPLOAD_FOLDER)
        file.save(filepath)
        
        # Save the filepath in MySQL database
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
            conn.commit()
        except mysql.connector.Error as err:
            return jsonify({'error': str(err)}), 500
        finally:
            cursor.close()
            conn.close()

        return jsonify({'message': 'File uploaded successfully', 'filepath': filepath}), 201

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    if not os.path.exists(os.path.join(UPLOAD_FOLDER, filename)):
        return jsonify({'error': 'File not found'}), 404
    return send_from_directory(directory=UPLOAD_FOLDER, path=filename)

if __name__ == '__main__':
    app.run(debug=True)


**Note:** Before running this code, ensure you have a MySQL database and table (`pdf_files`) set up with at least one column named `filepath` to store the file paths. Also, replace `'your_username'`, `'your_password'`, `'localhost'`, and `'your_database_name'` with your actual MySQL credentials and database name. You may need to install Flask and mysql-connector-python using pip if you haven't already:


pip install flask mysql-connector-python