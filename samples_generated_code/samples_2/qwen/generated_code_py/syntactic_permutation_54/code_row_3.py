from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# In-memory user database for demonstration purposes
users = {
    "admin": "password123"
}

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    if users.get(username) == password:
        return redirect(url_for('admin_page'))
    else:
        return "Invalid credentials"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)


