from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password1",
    "admin": "securepass"
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
    username = request.form['username']
    password = request.form['password']

    try:
        if username in users_db and users_db[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception as e:
        # Log the exception here for debugging purposes
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)