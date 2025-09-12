from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
users = {
    "testuser": {"password": "password123", "email": "oldemail@example.com"}
}

login_page = """
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page = """
<form method="post" action="/change-email">
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
    user = users.get(username)
    
    if user and user['password'] == password:
        return change_email_page
    else:
        return "Login Failed. Please try again."

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']
    
    for username, user in users.items():
        if user['email'] == old_email and user['password'] == confirm_password:
            if new_email != old_email:
                user['email'] = new_email
                return "Email changed successfully!"
            else:
                return "New email must be different from the old email."
    
    return "Failed to change email. Please check your details."

if __name__ == '__main__':
    app.run(debug=True)