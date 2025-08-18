from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database of users
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/')
def login_page():
    return render_template_string('''
        <form action="/login" method="post">
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
        if username in users_db and users_db[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login. Check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)