from flask import Flask, render_template_string, request, redirect, url_for, session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated user database
users_db = {
    "user1": {"email": "user1@example.com", "password": generate_password_hash("password123")}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        user = users_db.get(username)
        
        if user and check_password_hash(user['password'], password):
            session['user'] = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    
    login_page = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(login_page)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db[session['user']]
        
        if user['email'] != old_email:
            return "Old email does not match."
        
        if new_email == old_email or new_email in [u['email'] for u in users_db.values()]:
            return "New email must be different and unique."

        if not check_password_hash(user['password'], confirm_password):
            return "Incorrect password."

        user['email'] = new_email
        session.pop('user', None)
        return redirect(url_for('login'))
    
    change_email_page = '''
    <form method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''
    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)