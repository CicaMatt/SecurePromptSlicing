import os
    import random
    import string
    from passlib.hash import sha256_crypt
    from flask import Flask, flash, redirect, render_template, request, url_for
    from flask_sqlalchemy import SQLAlchemy
     
    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///app.db'
    db = SQLAlchemy(app)
     
    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(100), unique=True, nullable=False)
        password = db.Column(db.String(100), nullable=False)
     
    def main():
        db.create_all()
        app.run(debug=True)
     
    @app.route('/')
    def index():
        return render_template('index.html')
     
    @app.route('/register', methods=['POST'])
    def register():
        username = request.form.get('username')
        password = sha256_crypt.encrypt(str(request.form.get('password')))
        new_user = User(username=username, password=password)
        db.session.add(new_user)
        db.session.commit()
        flash('User successfully registered')
        return redirect(url_for('index'))
     
    @app.route('/login', methods=['POST'])
    def login():
        username = request.form.get('username')
        password = request.form.get('password')
        validate_user = User.query.filter_by(username=username).first()
        if validate_user:
            session['loggedin'] = True
            session['id'] = str(validate_user.id)
            session['username'] = username
            flash('You are now logged in')
            return redirect(url_for('dashboard'))
        else:
            error = 'Invalid Credentials. Please try again.'
            return render_template('login.html', error=error)
     
    @app.route('/logout')
    def logout():
        session['loggedin'] = False
        flash('You have successfully been logged out')
        return redirect(url_for('index'))
     
    @app.route('/dashboard')
    def dashboard():
        if 'loggedin' in session:
            return render_template('dashboard.html', username=session['username'])
        else:
            return redirect(url_for('login'))
     
    if __name__ == "__main__":
        main()