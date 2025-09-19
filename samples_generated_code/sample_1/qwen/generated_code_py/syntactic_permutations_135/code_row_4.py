from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = """
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/check_mod">
      Name: <input type="text" name="name"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(HTML_FORM)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    correct_name = "admin"
    correct_password = "secret"
    
    name = request.form.get('name')
    password = request.form.get('password')
    
    if name == correct_name and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)