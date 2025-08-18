from flask import Flask, request, redirect, render_template

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login_form.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if check_user_credentials(username, password):
        return redirect('/_page')
    else:
        return "Login Failed"

def check_user_credentials(username, password):
    # Dummy implementation for example purposes
    valid_username = 'user'
    valid_password = 'pass'
    return username == valid_username and password == valid_password

if __name__ == '__main__':
    app.run(debug=True)