from flask import Flask, request, redirect, url_for, render_template_string, session
import re

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123"}
}

def is_valid_email(email):
    return re.match(r"[^@]+@[^@]+\.[^@]+", email)

@app.route('/')
def login_page():
    if 'email' in session:
        return render_template_string('''
            <h2>Welcome, {{ email }}!</h2>
            <p><a href="/change-email">Change Email</a></p>
            <form action="/logout" method="post">
                <button type="submit">Logout</button>
            </form>
        ''', email=session['email'])
    return '''
        <form action="/login" method="post">
            <label for="email">Email:</label><br>
            <input type="text" id="email" name="email"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Login</button>
        </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if is_valid_email(email) and users_db.get(email, {}).get('password') == password:
        session['email'] = email
        return redirect(url_for('login_page'))
    return 'Invalid credentials', 401

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('email', None)
    return redirect(url_for('login_page'))

@app.route('/change-email')
def change_email_form():
    if 'email' not in session:
        return redirect(url_for('login_page'))
    
    return render_template_string('''
        <h2>Change Email</h2>
        <form action="/update-email" method="post">
            <label for="old_email">Old Email:</label><br>
            <input type="text" id="old_email" name="old_email" required><br>
            <label for="new_email">New Email:</label><br>
            <input type="text" id="new_email" name="new_email" required><br>
            <label for="confirm_password">Confirm Password:</label><br>
            <input type="password" id="confirm_password" name="confirm_password" required><br><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/update-email', methods=['POST'])
def update_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if 'email' not in session or session['email'] != old_email:
        return 'Unauthorized access', 403

    if not is_valid_email(new_email):
        return 'Invalid new email format', 400
    
    user_data = users_db.get(old_email)
    
    if not user_data or user_data['password'] != confirm_password:
        return 'Incorrect password', 401
    
    if new_email in users_db:
        return 'Email already exists', 409

    users_db[new_email] = {'password': user_data['password']}
    del users_db[old_email]
    session['email'] = new_email
    return redirect(url_for('login_page'))

if __name__ == '__main__':
    app.run(debug=True)