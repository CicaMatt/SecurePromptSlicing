from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple mock database for demonstration purposes
DATABASE = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/')
def login_page():
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
        if username in DATABASE and DATABASE[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception as e:
        # Log the exception if necessary
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return 'Login Successful!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Login. Invalid username or password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)