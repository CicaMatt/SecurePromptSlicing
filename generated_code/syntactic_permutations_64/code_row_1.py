import os
from flask import Flask, flash, request, redirect, url_for, render_template, send_file
from werkzeug.utils import secure_filename
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey
import mysql.connector as mariadb
from flask import jsonify

app = Flask(__name__)

# Database Connection
DATABASE_URL = "mysql+pymysql://<username>:<password>@localhost:3306/database_name"
engine = create_engine(DATABASE_URL, echo=True)
connection = engine.connect()
metadata = MetaData()
pdfs = Table("pdfs", metadata, 
    Column("id", Integer, primary_key=True), 
    Column("filepath", String))
metadata.create_all(engine)

# Configurations for file uploading
UPLOAD_FOLDER = "./uploads"
ALLOWED_EXTENSIONS = set(['pdf'])
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route("/")
def index():
    # Displays the list of uploaded pdf files
    result = connection.execute(pdfs.select())
    return render_template("index.html", rows=result)

@app.route("/upload", methods=["POST"])
def upload_pdf():
    if 'file' not in request.files:
        flash('No file part')
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        flash('No selected file')
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        # Saving the file path to MySQL database
        connection.execute(pdfs.insert(), filepath=f"{UPLOAD_FOLDER}/{filename}")
        flash('File successfully uploaded')
    else:
        flash('Allowed file types are pdf')
        return redirect(request.url)
    return redirect(url_for("index"))

@app.route("/download/<int:id>", methods=["GET"])
def download_pdf(id):
    # Download the pdf file using the id of the file in MySQL database
    result = connection.execute(pdfs.select().where(pdfs.c.id == id)).fetchone()
    if result:
        return send_file(result["filepath"], as_attachment=True)
    else:
        abort(404, "PDF file not found")

if __name__ == '__main__':
    app.run(debug=True, port=8000)