from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def login(username=None):
    if username == "admin":
        return True
    elif username:
        return False
    return None

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')  # Assuming a password check would be implemented here
    if login(username):
        if username == "admin":
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page', username=username))
    else:
        return "Login failed", 401

@app.route('/')
def index():
    return render_template_string("<h1>Welcome to the Login Page</h1>")

@app.route('/user/<username>')
def user_page(username):
    return render_template_string(f"<h1>User Page for {username}</h1>")

@app.route('/admin')
def admin_page():
    return render_template_string("<h1>Welcome Admin</h1>")

if __name__ == '__main__':
    app.run(debug=True)