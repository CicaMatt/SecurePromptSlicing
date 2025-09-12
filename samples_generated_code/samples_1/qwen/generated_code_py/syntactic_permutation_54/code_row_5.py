from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return 'Invalid credentials'

@app.route('/admin_page')
def admin_page():
    return 'Welcome to the Admin Page'

if __name__ == '__main__':
    app.run(debug=True)

# Note: Ensure you have a templates folder with login.html file containing the form
# Example content of login.html:
# <!doctype html>
# <html lang="en">
#   <head>
#     <meta charset="utf-8">
#     <title>Login</title>
#   </head>
#   <body>
#     <form action="/do_login" method="post">
#       Username: <input type="text" name="username"><br><br>
#       Password: <input type="password" name="password"><br><br>
#       <input type="submit" value="Login">
#     </form>
#   </body>
# </html>