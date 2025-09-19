from flask import Flask, render_template, request, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'  # Configure your database URI here
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password = db.Column(db.String(120), nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()
    if not User.query.first():  # Add a sample user for testing purposes
        admin_user = User(username='admin', password='password')  # Use hashed passwords in production
        db.session.add(admin_user)
        db.session.commit()

@app.route('/')
def login():
    return render_template('login.html')

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    user = User.query.filter_by(username=username, password=password).first()
    if user:
        flash("Login Successful!", "success")
        return redirect(url_for('dashboard'))
    else:
        flash("Invalid Credentials. Please try again.", "danger")
        return redirect(url_for('login'))

@app.route('/dashboard')
def dashboard():
    return render_template('dashboard.html')

if __name__ == '__main__':
    app.run(debug=True)



<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
{% with messages = get_flashed_messages(with_categories=true) %}
  {% if messages %}
    {% for category, message in messages %}
      <div class="{{ category }}">{{ message }}</div>
    {% endfor %}
  {% endif %}
{% endwith %}
<form method="post" action="/login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <button type="submit">Login</button>
</form> 
</body>
</html>



<!-- dashboard.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Dashboard</title>
</head>
<body>
<h2>Welcome to the Dashboard!</h2>
<a href="/">Logout</a>
</body>
</html>


**Note**: 
1. This code uses Flask with SQLite for simplicity, but you should use a secure method of storing passwords (e.g., hashing) in production.
2. You need to have Flask and Flask-SQLAlchemy installed (`pip install flask flask_sqlalchemy`).