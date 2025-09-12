from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if users.get(username) == password:
            return redirect(url_for('session_page', username=username))
        else:
            error_message = "Incorrect username or password"
            return render_template_string(login_html, error=error_message)
    return render_template_string(login_html)

@app.route('/session')
def session_page():
    username = request.args.get('username')
    if not username:
        return redirect(url_for('login'))
    return f"Welcome, {username}!"

login_html = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Login</title>
  </head>
  <body>
    <h1>Login</h1>
    {% if error %}
      <p style="color: red;">{{ error }}</p>
    {% endif %}
    <form method="post">
      <label for="username">Username:</label><br>
      <input type="text" id="username" name="username"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br>
      <button type="submit">Login</button>
    </form>
  </body>
</html>
"""

if __name__ == '__main__':
    app.run(debug=True)