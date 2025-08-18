import os
from flask import Flask, request
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        # Save the filepath to the MySQL database
        db_config = {
            'host': 'localhost',
            'user': 'yourusername',
            'password': 'yourpassword',
            'database': 'yourdatabase'
        }
        
        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            query = "INSERT INTO files (filepath) VALUES (%s)"
            cursor.execute(query, (filepath,))
            conn.commit()
        except mysql.connector.Error as err:
            return f"Failed to insert data into database: {err}"
        finally:
            if conn.is_connected():
                cursor.close()
                conn.close()

        # Use the filepath here...
        return 'File successfully uploaded and path saved'
    else:
        return 'Invalid file type'

if __name__ == '__main__':
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    app.run(debug=True)