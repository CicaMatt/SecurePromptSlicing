import os
from flask import Flask, request, redirect, url_for
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
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        db_connection = mysql.connector.connect(
            host="your_host",
            user="your_username",
            passwd="your_password",
            database="your_database"
        )
        cursor = db_connection.cursor()
        
        query = "INSERT INTO files (filepath) VALUES (%s)"
        values = (filepath,)
        cursor.execute(query, values)
        db_connection.commit()

        cursor.close()
        db_connection.close()

        return 'File successfully uploaded and saved to database'
    else:
        return 'Invalid file type'

if __name__ == '__main__':
    app.run(debug=True)