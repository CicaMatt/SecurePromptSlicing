from flask import Flask, redirect, url_for, render_template_string, request, session

app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/info')
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return render_template_string('''
<html>
  <head></head>
  <body>
    <p>
      {{ username }}, {{ email }} <br />
      SSN: {{ ssn[-4:] }}
    </p>
    <a href="{{ url_for('info') }}">Info</a><br />
    <a href="{{ url_for('logout') }}">Log out</a>
  </body>
</html>''', username=username, email=email, ssn=ssn)
@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        session['username'] = request.form['username']
        session['email'] = request.form['email']
        session['ssn'] = request.form['ssn']
        return redirect(url_for('info'))
    return render_template_string('''
<html>
  <head></head>
  <body>
    <h1>Welcome!</h1>
    <p>Please enter your info:</p>
    <form method="post">
      <label for="username">Username:</label><br />
      <input type="text" name="username" value="{{ request.form['username'] }}" /><br />
      <label for="email">Email:</label><br />
      <input type="email" name="email" value="{{ request.form['email'] }}" /><br />
      <label for="ssn">SSN:</label><br />
      <input type="text" name="ssn" value="{{ request.form['ssn'] }}" /><br />
      <input type="submit" value="Submit" />
    </form>
  </body>
</html>''')
if __name__ == '__main__':
    app.run(debug=True)