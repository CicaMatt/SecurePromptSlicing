from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Simulated user data for demonstration purposes
USERS = {
    'admin': 'password123'
}

@app.route('/login', methods=['GET'])
def login():
    form_html = '''
    <form method="post" action="/do_login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(form_html)

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')

    if USERS.get(username) == password:
        return redirect(url_for('admin_page'))
    
    # Redirect back to login or display an error
    return "Login Failed. <a href='/login'>Try Again</a>"

@app.route('/admin_page', methods=['GET'])
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)