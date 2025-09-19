from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user data for demonstration purposes
USER_DATA = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    try:
        if request.method == 'POST':
            username = request.form.get('username')
            password = request.form.get('password')

            # Simple authentication check
            if username in USER_DATA and USER_DATA[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
    except Exception as e:
        print(e)  # Log the error for debugging purposes
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login. Incorrect username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error occurred."

if __name__ == '__main__':
    app.run(debug=True)