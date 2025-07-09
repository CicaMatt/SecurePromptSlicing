import os
from PIL import Image
from io import BytesIO
import base64
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import create_engine
import uuid 

app = Flask(__name__)
UPLOAD_FOLDER='./uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)
app.config['UPLOAD_FOLDER']= UPLOAD_FOLDER
db = SQLAlchemy(app)

class Image(db.Model):
    id = db.Column(db.Integer, primary_key = True)
    name = db.Column(db.String(50), unique=True)
    image_base64 = db.Column(db.String(1024))

@app.route("/upload", methods = ['POST'])
def upload_image():
    try:
        file = request.files['file']
        img = Image.open(BytesIO(file.read()))
        filename, extension = os.path.splitext(file.filename)
        uuid_str= str(uuid.uuid4())
        image_name =  f"{uuid_str}{extension}"
        img.save(os.path.join(app.config['UPLOAD_FOLDER'],image_name))
        img_base64 = base64.b64encode(open(os.path.join(app.config['UPLOAD_FOLDER'],image_name),'rb').read())
        image=Image(name=image_name, image_base64=img_base64)
        db.session.add(image)
        db.session.commit()
    except Exception as e:
        print (e)
    return redirect("/")