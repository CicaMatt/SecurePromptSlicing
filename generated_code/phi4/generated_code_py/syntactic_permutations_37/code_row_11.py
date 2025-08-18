from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database for demonstration purposes.
DATABASE = {
    "user1": "password123",
    "user2": "pass456"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    try:
        if request.method == 'POST':
            username = request.form.get('username')
            password = request.form.get('password')

            # Check if the user exists and password matches
            if DATABASE.get(username) == password:
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
    return "Cannot login. Please check your credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error occurred."

if __name__ == '__main__':
    app.run(debug=True)