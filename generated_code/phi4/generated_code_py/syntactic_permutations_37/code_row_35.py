from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated database
database = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in database and database[username] == password:
        return redirect('/success')
    else:
        return redirect('/cant_login')

@app.route('/')
def index():
    # Simple HTML form
    html_form = '''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return html_form

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login, please check your credentials."

if __name__ == '__main__':
    app.run(debug=True)