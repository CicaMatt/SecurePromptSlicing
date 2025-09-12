from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "admin": "password123",
    "user": "secret"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if users_db.get(username) == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            return redirect('/internal_server_error')
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/success')
def success():
    return "Success! You are logged in."

@app.route('/cant_login')
def cant_login():
    return "Failed to log in. Please check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)