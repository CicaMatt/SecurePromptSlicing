from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy user database as a list of dictionaries for demonstration purposes
user_database = [
    {'username': 'user1', 'password': 'pass1'},
    {'username': 'user2', 'password': 'pass2'}
]

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form.get('username')
        password = request.form.get('password')

        if not username or not password:
            return redirect('/cant_login')

        for user in user_database:
            if user['username'] == username and user['password'] == password:
                return redirect('/success')

        return redirect('/cant_login')
    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return 'Login Successful!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Login. Please check your username and password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)