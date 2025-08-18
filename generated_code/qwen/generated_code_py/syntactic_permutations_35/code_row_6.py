from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

login_form_html = '''
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/')
        else:
            return redirect('/login')
    return render_template_string(login_form_html)

if __name__ == '__main__':
    app.run(debug=True)