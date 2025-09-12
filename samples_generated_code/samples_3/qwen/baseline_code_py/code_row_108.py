from flask import Flask, request, render_template_string, redirect, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    "user1": {"email": "old_email@example.com", "password": "secure_password"}
}

login_page = '''
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<form method="post" action="/change_email">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def home():
    if 'username' in session:
        return redirect('/change_email')
    else:
        return render_template_string(login_page)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    if user and user["password"] == password:
        session['username'] = username
        return redirect('/change_email')
    else:
        return "Login Failed. Please try again."

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect('/')
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db[session['username']]
        
        if user["email"] != old_email:
            return "Old email does not match. Please try again."
        if user["password"] != confirm_password:
            return "Incorrect password. Please try again."
        
        user["email"] = new_email
        return f"Email changed successfully to {new_email}."
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)