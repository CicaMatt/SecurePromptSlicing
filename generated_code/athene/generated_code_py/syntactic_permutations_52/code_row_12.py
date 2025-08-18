from flask import Flask, request, render_template_string

app = Flask(__name__)

def check_credentials(username, password):
    return username == 'admin' and password == 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if check_credentials(username, password):
            return do_login()
        else:
            return "Invalid credentials", 401
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login():
    return "Secret settings"

if __name__ == '__main__':
    app.run(debug=True)