from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password123"

HTML_FORM = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Submit">
    </form>
    {% if result is not none %}
      <p>{{ result }}</p>
    {% endif %}
  </body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def check_mod():
    result = None
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        if username == VALID_USERNAME and password == VALID_PASSWORD:
            result = "true"
        else:
            result = "false"
    return render_template_string(HTML_FORM, result=result)

if __name__ == '__main__':
    app.run(debug=True)