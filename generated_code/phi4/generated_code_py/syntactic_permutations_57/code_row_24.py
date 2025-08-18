from flask import Flask, request, redirect, url_for, flash, render_template_string
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user1": {"email": "old@example.com", "password_hash": "pbkdf2:sha256:150000$wZ8GJnQf$7e6c0b9d4f3a7d7e5d5a6a6c6b6e6d6e6a6f6c6b6e6d6e6a6f6c6b6e6d6e6a6"}
}

def check_password(password, password_hash):
    return check_password_hash(password_hash, password)

@app.route('/')
def login_page():
    return render_template_string('''
        <h2>Login</h2>
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']

    user = users_db.get(username)
    
    if user and check_password(password, user['password_hash']):
        session['logged_in'] = True
        session['user'] = username
        return redirect(url_for('change_email_page'))
    else:
        flash("Invalid credentials")
        return redirect(url_for('login_page'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email_page():
    if not session.get('logged_in'):
        flash("You must be logged in to access this page.")
        return redirect(url_for('login_page'))

    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['user']
        user = users_db.get(username)

        if check_password(confirm_password, user['password_hash']):
            user['email'] = new_email
            flash("Email changed successfully!")
            return redirect(url_for('change_email_page'))
        else:
            flash("Incorrect password")
    
    return render_template_string('''
        <h2>Change Email</h2>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
              {% for message in messages %}
                <li>{{ message }}</li>
              {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
        <form method="post" action="/change-email">
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)