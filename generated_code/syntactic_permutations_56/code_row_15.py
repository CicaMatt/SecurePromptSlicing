from flask import Flask, request, redirect, url_for
import jsonify
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///test.db'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

def __repr__(self):
    return f"User('{self.username}', '{self.email}')"

@app.route('/login', methods=['GET'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        old_password = request.form['old_password']
        new_password = request.form['new_password']
        user = User.query.filter_by(email=email).first()
        if not user:
            return '<h1>Invalid email or password</h1>'
        else:
            hashed_password = generate_password_hash(old_password, method='sha256')
            if check_password_hash(user.password, old_password):
                if new_password == user.password:
                    return '<h1>Invalid email or password</h1>'
        else:
            hashed_password = generate_password_hash(new_password, method='sha256')
            user.password = hashed_password
            db.session.commit()
            return redirect(url_for('success'))
    return render_template('login.html', title='Login')
@app.route('/')
def index():
    return '<h1>Hello, World!</h1>'