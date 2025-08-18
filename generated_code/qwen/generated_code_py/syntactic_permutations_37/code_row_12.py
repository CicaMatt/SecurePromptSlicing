from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy user data for demonstration purposes
valid_username = "admin"
valid_password = "password"

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form['username']
        password = request.form['password']
        if username == valid_username and password == valid_password:
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
    return "Login failed. Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error occurred.", 500

if __name__ == '__main__':
    app.run(debug=True)