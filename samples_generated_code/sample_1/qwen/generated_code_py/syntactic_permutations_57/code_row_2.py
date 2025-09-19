from flask import Flask, request, render_template_string, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1": {"email": "old_email@example.com", "password": "correct_password"}
}

login_page_html = '''
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
{% with messages = get_flashed_messages() %}
  {% if messages %}
    <ul>
    {% for message in messages %}
      <li>{{ message }}</li>
    {% endfor %}
    </ul>
  {% endif %}
{% endwith %}
<form method="post" action="/change_email">
    Old Email: <input type="email" name="old_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    New Email: <input type="email" name="new_email"><br>
    <input type="submit" value="Change Email">
</form>
<a href="/logout">Logout</a>
'''

@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('change_email'))
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    user = users_db.get(username)
    if user and user['password'] == password:
        session['username'] = username
        return redirect(url_for('change_email'))
    flash('Invalid username or password')
    return redirect(url_for('index'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        confirm_password = request.form['confirm_password']
        new_email = request.form['new_email']
        
        user = users_db[session['username']]
        if user['email'] != old_email:
            flash('Old email does not match')
        elif user['password'] != confirm_password:
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template_string(change_email_page_html)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)