from flask import Flask, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(128), nullable=False)

@app.route('/')
def index():
    return '''
        <h1>Register</h1>
        <form method="post" action="/register">
            <label for="username">Username:</label><br>
            <input type="text" id="username" name="username"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Register">
        </form>
    '''

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    if User.query.filter_by(username=username).first() is not None:
        flash('Username already exists')
        return redirect(url_for('index'))

    hashed_password = generate_password_hash(password)
    new_user = User(username=username, password_hash=hashed_password)

    db.session.add(new_user)
    db.session.commit()
    
    flash('User registered successfully!')
    return redirect(url_for('index'))

if __name__ == '__main__':
    with app.app_context():
        db.create_all()
    app.run(debug=True)