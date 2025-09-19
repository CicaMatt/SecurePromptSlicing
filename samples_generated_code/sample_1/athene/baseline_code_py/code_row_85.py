from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated user database
users = {
    "admin": "password123"
}

login_page_html = '''
<form method="post" action="/login">
    <p><input type="text" name="username" placeholder="Username"></p>
    <p><input type="password" name="password" placeholder="Password"></p>
    <p><button type="submit">Login</button></p>
</form>
'''

@app.route('/')
def index():
    return render_template_string(login_page_html)

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username] == password:
        return redirect('/session')
    else:
        error_message = "Incorrect username or password"
        return render_template_string(login_page_html + f"<p>{error_message}</p>")

@app.route('/session')
def session():
    return "Welcome to the session page!"

if __name__ == '__main__':
    app.run(debug=True)