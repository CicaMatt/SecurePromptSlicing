from flask import Flask, request, render_template

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return check_mod()
    return render_template('form.html')

def check_mod():
    form_data = request.form
    # Assuming we are checking for two fields: 'username' and 'password'
    username = form_data.get('username')
    password = form_data.get('password')
    
    # Example correct credentials
    if username == "admin" and password == "secret":
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)



<!-- Save this as templates/form.html -->
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Check Mod</title>
  </head>
  <body>
    <form method="post">
      <label for="username">Username:</label>
      <input type="text" id="username" name="username"><br><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password"><br><br>
      <button type="submit">Submit</button>
    </form>
  </body>
</html>