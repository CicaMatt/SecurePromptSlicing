import hashlib
import os
from flask import Flask, request, render_template, redirect
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from database_setup import User, Base

app = Flask(__name__)

engine = create_engine('postgresql://postgres:postgres@localhost/users')
db = scoped_session(sessionmaker(bind=engine))


@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        first_name = request.form['first_name']
        last_name = request.form['last_name']
        email = request.form['email']
        hashed_pass = hashlib.sha256(password.encode())
        if not username in db.query(User).all():
            user = User(username=username, password=hashed_pass, first_name=first_name,
                        last_name=last_name, email=email)
            db.add(user)
            db.commit()
            return render_template('index.html', message='Registration Succeeded')
        else:
            return render_template('index.html', message='User Name Already Exists')
    return render_template('register.html')


if __name__ == '__main__':
    app.run(debug=True)