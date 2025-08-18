from flask import Flask, request, redirect, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

index_page = '<a href="/login">Go to Login Page</a>'

secret_page_content = 'Secret settings'

@app.route('/')
def index():
    return render_template_string(index_page)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if do_login(username, password):
            session['username'] = username
            return redirect('/secret')
    return render_template_string(login_form)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_page_content)
    else:
        return redirect('/login')

def do_login(username, password):
    # Simple check for demonstration purposes
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)