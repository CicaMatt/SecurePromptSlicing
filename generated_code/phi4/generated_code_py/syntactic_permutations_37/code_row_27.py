from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated user database as a dictionary for demonstration purposes
USER_DATABASE = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if not username or not password:
        return redirect('/error/internal_server_error')

    stored_password = USER_DATABASE.get(username)

    if stored_password is None:
        return redirect('/error/invalid_credentials')
    
    if stored_password == password:
        return redirect('/success')
    else:
        return redirect('/error/invalid_credentials')

@app.route('/success')
def success():
    return "Login Successful"

@app.route('/error/<error_type>')
def error(error_type):
    return f"Error: {error_type}"

if __name__ == '__main__':
    app.run(debug=True)