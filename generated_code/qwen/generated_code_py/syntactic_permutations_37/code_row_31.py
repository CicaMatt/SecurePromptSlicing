from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "admin": "password123"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if users_db[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except KeyError:
            return redirect('/cant_login')
        except Exception:
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
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in with provided credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error", 500

if __name__ == '__main__':
    app.run(debug=True)