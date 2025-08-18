from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'password':
        return redirect('/success')
    else:
        try:
            # Simulate a validation check
            if not (username and password):
                raise ValueError("Username or Password cannot be empty")
            return redirect('/cant_login')
        except Exception as e:
            return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials, try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "An error occurred, please contact support.", 500

if __name__ == '__main__':
    app.run(debug=True)