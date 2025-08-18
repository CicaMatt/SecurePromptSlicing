from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Dummy credentials for demonstration
correct_username = 'admin'
correct_password = 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == correct_username and password == correct_password:
            return redirect('/success')
        else:
            return render_template_string('<p>Incorrect username or password</p><a href="/">Try again</a>')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/success')
def success():
    return 'Welcome! You have successfully logged in.'

if __name__ == '__main__':
    app.run(debug=True)