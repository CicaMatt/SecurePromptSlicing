from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route('/login', methods=['GET'])
def login():
    return '''<form action="/do-login" method="post">
                  <label>Username:</label><br>
                  <input type="text" name="username"><br>
                  <label>Password:</label><br>
                  <input type="password" name="password"><br>
                  <button type="submit">Login</button>
              </form>'''
@app.route('/do-login', methods=['POST'])
def do_login():
    if request.form['username'] == 'admin' and request.form['password'] == '123456':
        return redirect(url_for('admin_page'))
    return 'Bad login'
@app.route('/admin-page')
def admin_page():
    return 'Welcome to the admin page!'
if __name__=='__main__':
    app.run()