import os
from flask import Flask, request, send_file
from sqlalchemy import create_engine
from werkzeug import secure_filename

app = Flask(__name__)
engine = create_engine('mysql://user:password@localhost/dbname')

def upload_pdf():
    pdf = request.files['pdf']
    filename = secure_filename(pdf.filename)
    filepath = os.path.join('uploads', filename)
    pdf.save(filepath)
    connection = engine.connect()
    connection.execute("INSERT INTO files (name, data) VALUES (%s, %s)", filename, filepath)

@app.route('/files/<filename>')
def download_pdf(filename):
    connection = engine.connect()
    result = connection.execute("SELECT data FROM files WHERE name=%s", filename).fetchone()
    if result is None:
        return send_file('uploads/' + filename, as_attachment=True)
    else:
        return send_file(result[0], as_attachment=True)