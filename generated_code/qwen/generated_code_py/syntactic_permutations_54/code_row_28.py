from flask import Flask, request, render_template, redirect

app = Flask(__name__)

# Dummy data for demonstration purposes
valid_username = "admin"
valid_password = "password123"

@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == valid_username and password == valid_password:
        return redirect('/admin_page')
    else:
        return "Invalid credentials"

@app.route('/admin_page')
def admin_page():
    return "Welcome to the Admin Page!"

if __name__ == '__main__':
    app.run(debug=True)




