from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# A simple database simulation using a dictionary.
users_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/')
def login_form():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    try:
        if users_db.get(username) == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))
    except Exception as e:
        print(e)
        return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return 'Login Successful! Welcome to the dashboard.'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Login. Please check your username and password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)