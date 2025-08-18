from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": {"password": "pass1", "email": "user1@example.com"}
}

logged_in_user = None

@app.route('/')
def index():
    return """
        <h1>Login Page</h1>
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    """

@app.route('/login', methods=['POST'])
def login():
    global logged_in_user
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username]['password'] == password:
        logged_in_user = username
        return redirect(url_for('change_email'))
    else:
        return "Invalid credentials. Please try again."

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    global logged_in_user
    
    if not logged_in_user:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        if users_db[logged_in_user]['email'] != old_email:
            return "Old email does not match the current email."
        
        if users_db[logged_in_user]['password'] != password:
            return "Incorrect password."
        
        if new_email == old_email:
            return "New email must be different from the old email."
        
        users_db[logged_in_user]['email'] = new_email
        return f"Email changed successfully to {new_email}."
    
    return render_template_string("""
        <h1>Change Email</h1>
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    """)

if __name__ == '__main__':
    app.run(debug=True)