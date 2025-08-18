from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database of users
users_db = {
    "user1": "password1",
    "user2": "password2"
}

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
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in with provided credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error occurred.", 500

if __name__ == '__main__':
    app.run(debug=True)