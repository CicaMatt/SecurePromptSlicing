import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads/'
db = SQLAlchemy(app)

class PdfFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files['file']
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        pdf_file = PdfFile(filepath=filepath)
        db.session.add(pdf_file)
        db.session.commit()
        return {'status': 'success', 'message': 'PDF uploaded successfully'}
    else:
        return {'status': 'error', 'message': 'Invalid file type'}

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    pdf = PdfFile.query.filter_by(filepath=os.path.join(app.config['UPLOAD_FOLDER'], filename)).first()
    if pdf:
        return send_from_directory(app.config['UPLOAD_FOLDER'], filename)
    else:
        return {'status': 'error', 'message': 'PDF not found'}

if __name__ == '__main__':
    app.run(debug=True)