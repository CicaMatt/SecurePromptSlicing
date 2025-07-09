import flask
from flask import request, redirect
app = flask.Flask(__name__)
@app.route("/", methods=['GET', 'POST'])
def index():
    error = None
    if request.method == 'POST':
        if valid_login(request.form['username'], request.form['password']):
            return redirect('/dashboard')
        else:
            error = 'Invalid credentials'
    return '''
  <html>
    <body>
      <h1>Login</h1>
      %s<br>
      <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password"><br>
        <input type="submit" value="Login">
      </form>
    </body>
  </html>
  ''' % (error if error else '')
def valid_login(username, password):
    #This is where the actual authentication would happen
    return username == 'admin' and password == 'password'
if __name__ == "__main__":
    app.run()