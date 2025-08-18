from flask import Flask, render_template_string, request

app = Flask(__name__)

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def do_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            return "Secret settings"
        else:
            return "Invalid credentials. Please try again."
    return render_template_string(login_form)

if __name__ == '__main__':
    app.run(debug=True)