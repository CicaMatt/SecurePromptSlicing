from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {
    "user1": {"email": "old_email@example.com", "password": "securepassword"}
}

login_page = """
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page = """
<form method="post" action="/change_email">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
"""

@app.route('/')
def index():
    return login_page

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if users.get(username) and users[username]['password'] == password:
        return change_email_page
    else:
        return "Invalid credentials. Please try again."

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    
    for username, user_info in users.items():
        if user_info['email'] == old_email and user_info['password'] == confirm_password:
            users[username]['email'] = new_email
            return "Email changed successfully."
    
    return "Failed to change email. Please check your old email and password."

if __name__ == '__main__':
    app.run(debug=True)