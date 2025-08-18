from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database
users = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if users.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        except Exception:
            return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Log In"

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)