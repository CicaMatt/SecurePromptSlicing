from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database
users = {
    "admin": "password123"
}

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if users.get(username) == password:
            return redirect('/dashboard')
        else:
            return redirect('/login')
    return render_template_string(login_form)

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)