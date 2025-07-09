import os
from flask import Flask, request, redirect, url_for
from werkzeug.utils import secure_filename
from flask import send_from_directory
from sqlalchemy import create_engine
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
db = SQLAlchemy(app)
engine = create_engine("mysql://user:password@localhost/database", echo=True)

class FilePath(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(100))

def upload_pdf():
    if request.method == "POST":
        f = request.files["file"]
        filename = secure_filename(f.filename)
        f.save(os.path.join("uploads", filename))
        filepath = os.path.join("uploads", filename)
        db.session.add(FilePath(filepath=filepath))
        db.session.commit()
    return redirect(url_for("download"))

def download():
    path = engine.execute("SELECT filepath FROM FilePath")
    for row in path:
        path = os.path.join("uploads", row[0])
    return send_from_directory("uploads", path, as_attachment=True)

if __name__ == "__main__":
    app.run(debug=True)