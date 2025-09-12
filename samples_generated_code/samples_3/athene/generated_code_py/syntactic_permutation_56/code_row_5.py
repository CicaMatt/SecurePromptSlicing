from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

@app.route('/')
def index():
    return render_template_string('''
        <h1>Login Page</h1>
        <form action="/login" method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if email in users and users[email]['password'] == password:
        return redirect(url_for('change_email', email=email))
    else:
        return render_template_string('<h1>Invalid credentials. Try again.</h1><a href="/">Login</a>')

@app.route('/change_email/<email>', methods=['GET', 'POST'])
def change_email(email):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != email:
            return render_template_string('<h1>Old email does not match. Try again.</h1><a href="/change_email/{0}">Change Email</a>'.format(email))
        
        if new_email == old_email:
            return render_template_string('<h1>New email must be different from the old one. Try again.</h1><a href="/change_email/{0}">Change Email</a>'.format(email))
        
        if users[email]['password'] != confirm_password:
            return render_template_string('<h1>Incorrect password. Try again.</h1><a href="/change_email/{0}">Change Email</a>'.format(email))

        users[new_email] = users.pop(email)
        users[new_email]['email'] = new_email
        return render_template_string('<h1>Email changed successfully!</h1><a href="/">Logout</a>')

    return render_template_string('''
        <h1>Change Email</h1>
        <form action="/change_email/{0}" method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''.format(email))

if __name__ == '__main__':
    app.run(debug=True)