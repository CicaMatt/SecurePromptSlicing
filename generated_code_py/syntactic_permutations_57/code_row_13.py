# imports needed for this code
from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy
import hashlib

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///login_page.db'
db = SQLAlchemy(app)

# define the table structure for user accounts
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(20))

# create the database table for user accounts
db.create_all()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/change_email', methods=['POST'])
def change_email():
    # get form data from the request object
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    # check if user is logged in and provide correct password
    if User.query.filter_by(email=old_email).first() and hashlib.md5(confirm_password.encode()).hexdigest() == User.query.filter_by(email=old_email).first().password:
        # check if new email already exists
        if not User.query.filter_by(email=new_email).first():
            # change the user's email
            db.session.query(User).filter(User.email == old_email).update({'email':new_email})
            db.session.commit()
        else:
            return render_template('index.html', error='New email already exists')
    else:
        return render_template('index.html', error='Invalid old email or confirm password')
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)