from flask import Flask, request, redirect, render_template_string, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

login_page = '''
<form action="/login" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
{% with messages = get_flashed_messages() %}
  {% if messages %}
    <ul>
    {% for message in messages %}
      <li>{{ message }}</li>
    {% endfor %}
    </ul>
  {% endif %}
{% endwith %}
<form action="/change_email" method="post">
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def index():
    if 'username' in session:
        return redirect('/change_email')
    else:
        return login_page

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if username in users and users[username]['password'] == password:
        session['username'] = username
        return redirect('/change_email')
    else:
        flash('Invalid credentials')
        return redirect('/')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect('/')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect('/')
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        username = session['username']
        user = users[username]
        
        if user['password'] != confirm_password:
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email changed successfully')
    
    return change_email_page

if __name__ == '__main__':
    app.run(debug=True)