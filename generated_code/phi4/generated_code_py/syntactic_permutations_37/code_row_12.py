from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if username == VALID_USERNAME and password == VALID_PASSWORD:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # Log the error for debugging purposes
            print(f"Internal Server Error: {e}")
            return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login! Invalid Credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "500 Internal Server Error"

if __name__ == '__main__':
    app.run(debug=True)


