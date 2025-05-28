import uuid
import os
from flask import Flask, request, jsonify
from flask_mysqldb import MySQL
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = 'password'
app.config['MYSQL_DB'] = 'mydatabase'
mysql = MySQL(app)

def upload_pdf():
    if 'file' not in request.files:
        return jsonify({"error": "No file part"}), 400
    file = request.files['file']
    if file.filename == '':
        return jsonify({"error": "No selected file"}), 400
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOADS_FOLDER'], filename)
        file.save(filepath)
        cursor = mysql.connection.cursor()
        cursor.execute("INSERT INTO pdfs (filepath) VALUES (%s)", (filepath,))
        mysql.connection.commit()
        cursor.close()
        return jsonify({"success": "File uploaded successfully"}), 201
    else:
        return jsonify({"error": "Unsupported file type"}), 400

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route("/download/<int:id>")
def download(id):
    cursor = mysql.connection.cursor()
    result = cursor.execute("SELECT * FROM pdfs WHERE id=%s", (id,))
    if result > 0:
        row = cursor.fetchone()
        filename = row[1]
        return send_file(filename, as_attachment=True)
    else:
        cursor.close()
        return jsonify({"error": "File not found"}), 404

if __name__ == '__main__':
    app.run()