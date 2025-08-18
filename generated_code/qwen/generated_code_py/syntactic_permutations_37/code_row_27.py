from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database of users
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/')
def login():
    return render_template_string(login_form)

@app.route('/login', methods=['POST'])
def check_login():
    try:
        username = request.form['username']
        password = request.form['password']
        
        if users_db.get(username) == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('failure'))
    except Exception as e:
        return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/failure')
def failure():
    return "Login failed. Please try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error", 500

if __name__ == '__main__':
    app.run(debug=True)