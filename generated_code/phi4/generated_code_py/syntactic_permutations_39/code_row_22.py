from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <title>Login Page</title>
  </head>
  <body>
    <h2>Login</h2>
    <form method="post">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <button type="submit">Login</button>
    </form>
    {% if error %}
    <p style="color:red;">{{ error }}</p>
    {% endif %}
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            return redirect(url_for('success'))
        else:
            error_message = "Invalid username or password."
            return render_template_string(HTML_TEMPLATE, error=error_message)
    
    return render_template_string(HTML_TEMPLATE)

@app.route('/success')
def success():
    return "Login successful! Welcome!"

if __name__ == '__main__':
    app.run(debug=True)