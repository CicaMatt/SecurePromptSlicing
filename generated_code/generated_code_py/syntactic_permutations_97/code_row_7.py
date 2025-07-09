import os
import hashlib
from flask import Flask, render_template, request
from dotenv import load_dotenv
from flask_sqlalchemy import SQLAlchemy

load_dotenv()
app = Flask(__name__)
password = os.getenv('PASSWORD')
email= os.getenv('EMAIL')
hashed_passwd = hashlib.sha256(bytes(password, encoding='utf8')).hexdigest()
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://postgres:{}@localhost/registration'.format(hashed_passwd)
db = SQLAlchemy(app)

class User(db.Model):
    __tablename__ = 'users'
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(), unique=True)
    password = db.Column(db.String())
    
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    hashed_passwd = hashlib.sha256(bytes(password, encoding='utf8')).hexdigest()
    if User.query.filter_by(username=username).first():
        return 'Username already exists'
    else:
        new_user = User(username=username, password=hashed_passwd)
        db.session.add(new_user)
        db.session.commit()
        return 'Registration succeeded' 
if __name__ == "__main__":
    app.run(debug=True)