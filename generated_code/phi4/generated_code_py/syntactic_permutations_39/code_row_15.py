from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simple user database for demonstration purposes
users_db = {
    'username': 'password'  # Replace with actual usernames and passwords as needed
}

login_page_html = '''
<!doctype html>
<title>Login</title>
<h1>Login</h1>
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
{% if error %}
<p style="color: red;">{{ error }}</p>
{% endif %}
'''

session_page_html = '''
<!doctype html>
<title>Session</title>
<h1>Welcome to the session page!</h1>
<a href="/">Logout</a>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect('/session')
        else:
            return render_template_string(login_page_html, error="Invalid username or password.")
    
    return render_template_string(login_page_html)

@app.route('/session')
def session():
    return render_template_string(session_page_html)

if __name__ == '__main__':
    app.run(debug=True)