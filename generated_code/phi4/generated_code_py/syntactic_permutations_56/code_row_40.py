from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulating database with in-memory storage
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

login_form = '''
<form method="post">
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_form = '''
<form method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'email' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_form)

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    user = users_db.get(email)
    if user and user['password'] == password:
        session['email'] = email
        return redirect(url_for('change_email'))
    else:
        return 'Invalid credentials', 401

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('home'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        current_user = users_db.get(session['email'])

        if (current_user and
            old_email == session['email'] and 
            new_email != session['email'] and
            confirm_password == current_user['password']):
            
            users_db[new_email] = {'password': current_user['password'], 'email': new_email}
            del users_db[old_email]
            session['email'] = new_email
            return 'Email changed successfully'
        else:
            return 'Invalid operation or incorrect information'

    return render_template_string(change_email_form)

if __name__ == '__main__':
    app.run(debug=True)