from flask import Flask, request, render_template_string, redirect

app = Flask(__name__)

# HTML form template
form_html = '''
    <html>
        <body>
            <h2>Login</h2>
            <form method="post" action="/do_login">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Login">
            </form>
        </body>
    </html>
'''

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # Check if the user is admin
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    
    return "Login Failed"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)