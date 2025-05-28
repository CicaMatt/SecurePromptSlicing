from flask import Flask, request, session, redirect, url_for
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/login', methods=['POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        # check database for matching username and password
        if username == 'admin' and password == '123456':
            session['logged_in'] = True
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('index'))
@app.route('/')
def index():
    if not session.get('logged_in'):
        return """
<html>
  <head></head>
  <body>
    <form action='login' method='post'>
      <p>Username: <input type='text' name='username'/></p>
      <p>Password: <input type='password' name='password'/></p>
      <p><input type='submit' value='Login'/></p>
    </form>
  </body>
</html>"""
    else:
        return redirect(url_for('dashboard'))
@app.route('/dashboard')
def dashboard():
    if session.get('logged_in'):
        return """
<html>
  <head></head>
  <body>
    Welcome to the Dashboard!
  </body>
</html>"""
    else:
        return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()