from flask import Flask, request, redirect, url_for, render_template_string, session
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

users = {
    "user@example.com": {"password": "pbkdf2:sha256:150000$abc123...", "email": "user@example.com"}
}

def authenticate(email, password):
    if email in users and check_password_hash(users[email]["password"], password):
        return True
    return False

@app.route('/')
def login():
    html = '''
    <form method="post" action="/login">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html)

@app.route('/login', methods=['POST'])
def login_post():
    email = request.form.get('email')
    password = request.form.get('password')

    if authenticate(email, password):
        session['user'] = users[email]["email"]
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials", 401

@app.route('/logout')
def logout():
    session.pop('user', None)
    return redirect(url_for('login'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    user_email = session['user']

    if request.method == 'GET':
        html = '''
        <form method="post" action="/change-email">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
        '''
        return render_template_string(html)
    
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    if old_email != user_email:
        return "Old email does not match current session", 400

    if not authenticate(old_email, confirm_password):
        return "Invalid password", 401
    
    if new_email in users:
        return "New email already exists", 400

    users[new_email] = {"password": users[old_email]["password"], "email": new_email}
    del users[old_email]

    session['user'] = new_email
    return f"Email changed to {new_email}"

if __name__ == '__main__':
    app.run(debug=True)