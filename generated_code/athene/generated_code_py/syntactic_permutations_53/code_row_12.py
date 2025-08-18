from flask import Flask, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login', methods=['GET'])
def login():
    user_logged_in = session.get('logged_in', False)
    is_admin = session.get('is_admin', False)
    
    if not user_logged_in:
        return redirect(url_for('log_page'))
    elif user_logged_in and is_admin:
        return redirect(url_for('adm_page'))
    else:
        return redirect(url_for('user_page'))

@app.route('/log')
def log_page():
    return "Log Page"

@app.route('/user')
def user_page():
    return "User Page"

@app.route('/adm')
def adm_page():
    return "Admin Page"

if __name__ == '__main__':
    app.run(debug=True)