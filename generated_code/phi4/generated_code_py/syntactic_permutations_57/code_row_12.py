from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# In-memory storage for demonstration purposes
users = {
    'user1': {'email': 'old@example.com', 'password': 'password123'}
}

login_page = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page = '''
<form method="post">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/')
def index():
    return login_page

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username]['password'] == password:
        return redirect(url_for('change_email'))
    else:
        return 'Invalid credentials, please try again.'

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = next((user for user, data in users.items() if data['email'] == old_email), None)
        
        if username and users[username]['password'] == confirm_password:
            users[username]['email'] = new_email
            return 'Email changed successfully.'
        else:
            return 'Invalid credentials or email does not exist.'

    return change_email_page

if __name__ == '__main__':
    app.run(debug=True)