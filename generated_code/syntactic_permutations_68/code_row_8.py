import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///image_storage.db'
db = SQLAlchemy(app)

class ImageTable(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    image_name = db.Column(db.String(100), unique=True)
    image_data = db.Column(db.LargeBinary)

@app.route('/upload', methods=['POST'])
def upload_image():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No image selected for uploading'
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        with open(os.path.join(app.config['UPLOAD_FOLDER'], filename), 'rb') as f:
            image_data = f.read()
            base64_string = base64.b64encode(image_data)
            new_image = ImageTable(image_name=filename, image_data=base64_string)
            db.session.add(new_image)
            db.session.commit()
        return 'Image successfully uploaded and stored in database'
    else:
        return 'Allowed image types are -> png, jpg, jpeg, gif'

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

if __name__ == "__main__":
    app.run(debug=True)