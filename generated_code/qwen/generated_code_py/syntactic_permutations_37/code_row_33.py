from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def login():
    return render_template_string('''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')
    
    try:
        if users[username] == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except KeyError:
        return redirect('/cant_login')

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login. Please try again."

if __name__ == '__main__':
    app.run(debug=True)