from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123",
    "user": "mypassword"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if users_db.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('login_failure'))
        except Exception as e:
            return redirect(url_for('internal_server_error'))

    login_form = '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''
    return render_template_string(login_form)

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/login_failure')
def login_failure():
    return "Login Failed. Please try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)