import os
from flask import Flask, request, send_file
from flask_mysqldb import MySQL

app = Flask(__name__)

app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'mydatabase'

mysql = MySQL(app)

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if request.method == 'POST':
        file = request.files['file']
        filename = file.filename
        filepath = os.path.join('uploads', filename)
        file.save(filepath)

        cur = mysql.connection.cursor()
        cur.execute("INSERT INTO pdfs (name, path) VALUES (%s, %s)", (filename, filepath))
        mysql.connection.commit()
        cur.close()
    return 'File uploaded successfully'

@app.route('/download/<string:name>', methods=['GET'])
def download_pdf(name):
    if request.method == 'GET':
        cur = mysql.connection.cursor()
        result = cur.execute("SELECT * FROM pdfs WHERE name=%s", [name])
        data = cur.fetchone()
        filepath = data['path']
        return send_file(filepath, as_attachment=True)