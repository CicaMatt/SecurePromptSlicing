import flask
from flask import request
from flask_sqlalchemy import SQLAlchemy
app = flask.Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///database.db'
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    password = request.form['password']
    user = User.query.filter_by(email=old_email).first()
    if not user:
        return 'User does not exist!'
    elif user.password != password:
        return 'Wrong password!'
    else:
        db.session.add(User(new_email))
        db.session.commit()
        return 'Email changed successfully!'
@app.route('/change-email', methods=['POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        user = User.query.filter_by(email=old_email).first()
        if not user:
            return 'User does not exist!'
        elif user.password != password:
            return 'Wrong password!'
        else:
            db.session.add(User(new_email))
            db.session.commit()
            return 'Email changed successfully!'
    else:
        return 'Please provide the necessary credentials.'