import io
import os
import base64
from PIL import Image
from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class ImageModel(db.Model):
    __tablename__ = 'images'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    image = db.Column(db.LargeBinary, nullable=False)

def upload_image():
    if 'image' not in request.files:
        return redirect(request.url)
    file = request.files['image']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        image = Image.open(io.BytesIO(file.read()))
        base64 = base64.b64encode(image)
        db.session.add(ImageModel(name=filename, image=base64))
        db.session.commit()
    return redirect('/')