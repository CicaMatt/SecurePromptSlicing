from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'correct_username' and password == 'correct_password':
        return redirect('/success')
    else:
        return "Incorrect username or password"

@app.route('/success')
def success():
    return "Login successful!"

if __name__ == '__main__':
    app.run(debug=True)