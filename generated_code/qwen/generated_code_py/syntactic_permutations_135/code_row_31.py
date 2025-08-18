from flask import Flask, request, render_template_string

app = Flask(__name__)

HTML_FORM = '''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post" action="/check_mod">
      Username: <input type="text" name="username"><br><br>
      Password: <input type="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
'''

@app.route('/', methods=['GET'])
def index():
    return render_template_string(HTML_FORM)

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    
    # Example correct credentials
    if username == 'admin' and password == 'secret':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)