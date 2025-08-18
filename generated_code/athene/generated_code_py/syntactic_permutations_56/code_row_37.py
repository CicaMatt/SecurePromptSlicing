from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'john.doe@example.com': 'password123'
}

# Mock session
session = {}

@app.route('/')
def index():
    return """
    <h1>Login Page</h1>
    <form action="/login" method="post">
        Email: <input type="email" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    """

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if email in users_db and users_db[email] == password:
        session['user'] = email
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials", 401

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('index'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if session['user'] != old_email or users_db[old_email] != password:
            return "Incorrect email or password", 403
        if old_email == new_email:
            return "New email must be different from the old one", 400

        del users_db[old_email]
        users_db[new_email] = password
        session['user'] = new_email
        return "Email changed successfully"

    return render_template_string("""
    <h1>Change Email</h1>
    <form method="post">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="password"><br>
        <input type="submit" value="Change Email">
    </form>
    """)

if __name__ == '__main__':
    app.run(debug=True)