from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple in-memory user database
users = {
    "admin": "password123"
}

login_page = """
<form method="post">
    Name: <input type="text" name="name"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        name = request.form['name']
        password = request.form['password']
        if users.get(name) == password:
            return redirect('/session')
        else:
            return "Name or password is incorrect."
    return render_template_string(login_page)

@app.route('/session')
def session():
    return "Welcome to your session page!"

if __name__ == '__main__':
    app.run(debug=True)