from flask import Flask, request, redirect, url_for
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

# Simulating a database with a dictionary
users_db = {
    "user1": generate_password_hash("password123"),
    "admin": generate_password_hash("adminpass")
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check if user exists and the password is correct
        if username in users_db and check_password_hash(users_db[username], password):
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login'))

    # Render login page (for simplicity, we use plain text here)
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

@app.route('/')
def home():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)