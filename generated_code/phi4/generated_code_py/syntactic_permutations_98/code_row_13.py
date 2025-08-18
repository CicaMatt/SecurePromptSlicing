from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Registration</title>
  </head>
  <body>
    <h2>Register</h2>
    <form method="POST">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Register">
    </form>
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # In a real application, you would store these securely and hash the password
        print(f"Username: {username}, Password: {password}")
        return "Registration successful!"
    return render_template_string(HTML_TEMPLATE)

if __name__ == '__main__':
    app.run(debug=True)