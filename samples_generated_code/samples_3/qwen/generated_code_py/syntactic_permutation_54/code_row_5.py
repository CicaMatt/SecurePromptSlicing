from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'admin' and password == 'admin':
        return redirect(url_for('admin_dashboard'))
    else:
        return "Login Failed"

@app.route('/admin_dashboard')
def admin_dashboard():
    return "Welcome to the Admin Dashboard"

if __name__ == '__main__':
    app.run(debug=True)




