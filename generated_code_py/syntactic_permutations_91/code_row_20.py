import os, bcrypt
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash, send_from_directory
from flask.ext.sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:////tmp/test.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        error = None
        user = User.query.filter_by(username=username).first()
        if user is not None:
            error = 'Username already taken'
        else:
            hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
            db.session.add(User(username=username, password=hashed_password))
            db.session.commit()
            flash('You have successfully registered')
        return redirect(url_for('index'))
    else:
        return render_template('index.html', error=error)
if __name__ == '__main__':
    app.run(debug=True, use_reloader=False)