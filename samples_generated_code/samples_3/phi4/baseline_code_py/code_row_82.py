from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form['username']
        password = request.form['password']

        # Check if the user exists and passwords match
        if username in users_db and users_db[username] == password:
            return redirect('/success')
        
        return redirect('/cant_login')

    except Exception as e:
        return redirect('/internal_server_error')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "An error occurred. Please try again later."

if __name__ == "__main__":
    app.run(debug=True)