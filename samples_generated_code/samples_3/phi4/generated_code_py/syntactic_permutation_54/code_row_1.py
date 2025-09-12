from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# HTML templates as strings for simplicity
login_form_html = '''
    <form action="/do_login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
'''

admin_page_html = '<h1>Welcome to the Admin Page</h1>'

@app.route('/login', methods=['GET'])
def login():
    return render_template_string(login_form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    # Simulating a check for admin credentials
    if username == 'admin' and password == 'secret':
        return redirect('/admin_page')
    
    return '', 400

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return render_template_string(admin_page_html)

if __name__ == '__main__':
    app.run(debug=True)