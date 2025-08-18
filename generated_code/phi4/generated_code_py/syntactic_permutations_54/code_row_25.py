from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form_html = """
<form method="post" action="/do_login">
    <label for="username">Username:</label><br>
    <input type="text" id="username" name="username"><br>
    <label for="password">Password:</label><br>
    <input type="password" id="password" name="password"><br><br>
    <input type="submit" value="Submit">
</form> 
"""

admin_page_html = "<h1>Welcome to the Admin Page!</h1>"

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']

    # Dummy check for admin
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_page'))
    
    return "Login failed or not an admin."

@app.route('/admin')
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)