import bcrypt
from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secretkey'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password.encode('utf-8'), salt)

        # store the username, hashed_password and salt in database

        flash('Registration successful!')
        return redirect(url_for('index'))
    return render_template('register.html')

if __name__ == "__main__":
    app.run(debug=True)