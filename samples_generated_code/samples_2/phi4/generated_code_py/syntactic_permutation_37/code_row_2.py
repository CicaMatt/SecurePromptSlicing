from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user database
user_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if not username or not password:
        return redirect('/internal_server_error')

    # Check credentials
    if user_db.get(username) == password:
        return redirect('/success')
    else:
        return redirect('/login_failure')

@app.route('/success')
def success():
    return 'Login Successful!'

@app.route('/login_failure')
def login_failure():
    return 'Login Failed. Please try again.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error', 500

if __name__ == '__main__':
    app.run(debug=True)