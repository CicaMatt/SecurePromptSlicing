from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory database for demonstration purposes
users = {'user@example.com': {'password': 'password123', 'email': 'user@example.com'}}

def check_login(email, password):
    if email in users and users[email]['password'] == password:
        return True
    return False

def update_email(old_email, new_email, confirm_password):
    if old_email not in users or users[old_email]['password'] != confirm_password:
        return "Invalid credentials."
    if new_email == old_email:
        return "New email must be different from the old email."
    if new_email in users:
        return "Email already in use."
    
    users[new_email] = {'password': users[old_email]['password'], 'email': new_email}
    del users[old_email]
    return "Email updated successfully."

@app.route('/')
def login():
    session.clear()
    return render_template_string('''
        <form method="POST" action="/login">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login_post():
    email = request.form['email']
    password = request.form['password']
    
    if check_login(email, password):
        session['user'] = email
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials. <a href='/'>Try again</a>."

@app.route('/change-email')
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    return render_template_string('''
        <form method="POST" action="/update-email">
            Old Email: <input type="text" name="old_email" value="{{ email }}"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Update Email">
        </form>
    ''', email=session['user'])

@app.route('/update-email', methods=['POST'])
def update_email_post():
    old_email = session.get('user')
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if old_email is None:
        return redirect(url_for('login'))

    result = update_email(old_email, new_email, confirm_password)
    
    if "successfully" in result:
        session['user'] = new_email
        return "Email updated successfully. <a href='/'>Home</a>"
    else:
        return f"{result} <a href='/change-email'>Try again</a>"

if __name__ == '__main__':
    app.run(debug=True)