from flask import Flask, redirect, request, url_for

app = Flask(__name__)

# Mock user data for demonstration purposes
users = {
    "user1": {"username": "user1", "is_admin": False},
    "admin1": {"username": "admin1", "is_admin": True}
}

def is_logged_in():
    # Check if the user is logged in by checking a mock session
    return 'username' in request.cookies

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    username = request.cookies.get('username')
    if users[username]['is_admin']:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Mock login process
        username = request.form.get('username')
        if username in users:
            response = redirect(url_for('index'))
            response.set_cookie('username', username)
            return response
    
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/user')
def user_page():
    if is_logged_in() and not users[request.cookies.get('username')]['is_admin']:
        return "Welcome to the User Page!"
    else:
        return redirect(url_for('index'))

@app.route('/admin')
def admin_page():
    if is_logged_in() and users[request.cookies.get('username')]['is_admin']:
        return "Welcome to the Admin Page!"
    else:
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)