from flask import Flask, redirect, request, session, url_for

app = Flask(__name__)
app.secret_key = 'your_secret_key'

def login_required(f):
    def decorated_function(*args, **kwargs):
        if 'username' not in session:
            return redirect(url_for('login'))
        return f(*args, **kwargs)
    return decorated_function

def admin_required(f):
    @login_required
    def decorated_function(*args, **kwargs):
        if session.get('is_admin', False) is not True:
            return redirect(url_for('user_page'))
        return f(*args, **kwargs)
    return decorated_function

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        session['username'] = request.form['username']
        session['is_admin'] = request.form.get('is_admin') == 'on'
        if session['is_admin']:
            return redirect(url_for('admin_page'))
        else:
            return redirect(url_for('user_page'))
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Is Admin: <input type="checkbox" name="is_admin"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/user')
@login_required
def user_page():
    return 'Welcome to the User Page'

@app.route('/admin')
@admin_required
def admin_page():
    return 'Welcome to the Admin Page'

if __name__ == '__main__':
    app.run(debug=True)