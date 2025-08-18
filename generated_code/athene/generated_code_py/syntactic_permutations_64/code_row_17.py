import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads/'
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
db = SQLAlchemy(app)

class PdfFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files['file']
    if file:
        filename = file.filename
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        pdf_file = PdfFile(filepath=filepath)
        db.session.add(pdf_file)
        db.session.commit()
        
        return {'message': 'PDF uploaded successfully', 'filepath': filepath}, 201

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    file = PdfFile.query.get(file_id)
    if file:
        directory, filename = os.path.split(file.filepath)
        return send_from_directory(directory, filename, as_attachment=True)
    else:
        return {'error': 'File not found'}, 404

if __name__ == '__main__':
    app.run(debug=True)