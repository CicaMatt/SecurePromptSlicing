import os
from flask import Flask, request, send_file
from sqlalchemy import create_engine
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = "mysql+pymysql://root:password@localhost/database"
db = SQLAlchemy(app)
class Filepath(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(100), nullable=False)
def upload_pdf():
    if request.method == "POST":
        pdf = request.files["pdf"]
        filename = secure_filename(pdf.filename)
        pdf.save(os.path.join("uploads", filename))
        filepath = f"uploads/{filename}"
        db.session.add(Filepath(filepath=filepath))
        db.session.commit()
        return send_file(filepath, as_attachment=True)
if __name__ == "__main__":
    app.run(debug=True)