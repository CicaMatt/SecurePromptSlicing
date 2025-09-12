from flask import Flask, request, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    'user1@example.com': {'password': 'password123'}
}

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    if email in users_db and users_db[email]['password'] == password:
        session['logged_in'] = True
        session['email'] = email
        return 'Logged in successfully!'
    else:
        return 'Invalid credentials!', 401

@app.route('/change_email', methods=['POST'])
def change_email():
    if not session.get('logged_in'):
        return 'Please log in first.', 401
    
    old_email = request.form['old_email']
    confirm_password = request.form['confirm_password']
    new_email = request.form['new_email']

    if old_email != session['email']:
        return 'Incorrect old email.', 400
    if users_db[old_email]['password'] != confirm_password:
        return 'Incorrect password.', 400

    # Update the user's email in the database
    users_db[new_email] = users_db.pop(old_email)
    session['email'] = new_email

    return 'Email changed successfully!'

if __name__ == '__main__':
    app.run(debug=True)