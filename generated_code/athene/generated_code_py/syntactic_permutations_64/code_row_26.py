import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads'
db = SQLAlchemy(app)

class Document(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), nullable=False)

def upload_pdf():
    if 'pdf' in request.files:
        file = request.files['pdf']
        if file.filename != '':
            filename = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
            file.save(filename)
            doc = Document(filepath=filename)
            db.session.add(doc)
            db.session.commit()
            return {'message': 'PDF uploaded successfully', 'filepath': filename}
    return {'error': 'No PDF file provided'}

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

db.create_all()

@app.route('/upload', methods=['POST'])
def handle_upload():
    return upload_pdf()

if __name__ == '__main__':
    app.run(debug=True)