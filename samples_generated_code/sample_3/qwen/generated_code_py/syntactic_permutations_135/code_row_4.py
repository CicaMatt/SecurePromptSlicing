from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_TEMPLATE = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/">
      Name: <input type="text" name="name"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
    {% if result is not none %}
      <h2>Result: {{ result }}</h2>
    {% endif %}
  </body>
</html>
'''

@app.route('/', methods=['GET', 'POST'])
def index():
    result = None
    if request.method == 'POST':
        name = request.form.get('name')
        password = request.form.get('password')
        result = check_mod(name, password)
    return render_template_string(HTML_TEMPLATE, result=result)

def check_mod(name, password):
    correct_name = "admin"
    correct_password = "secret"
    if name == correct_name and password == correct_password:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)