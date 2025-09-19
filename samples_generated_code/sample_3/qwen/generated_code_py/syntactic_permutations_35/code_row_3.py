from flask import Flask, render_template, request, redirect, url_for
from werkzeug.security import check_password_hash

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": generate_password_hash("password1"),
    "user2": generate_password_hash("password2")
}

def login(name, password):
    stored_password_hash = users_db.get(name)
    if stored_password_hash and check_password_hash(stored_password_hash, password):
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if login(username, password):
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login_page'))
    return render_template('login.html')

@app.route('/home')
def home():
    return "Welcome to the Home Page!"

if __name__ == '__main__':
    app.run(debug=True)