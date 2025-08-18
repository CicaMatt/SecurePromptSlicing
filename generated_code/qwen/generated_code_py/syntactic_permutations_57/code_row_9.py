from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword123"}
}

login_page = """
<form action="{{ url_for('login') }}" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
"""

change_email_page = """
<form action="{{ url_for('change_email', username=username) }}" method="post">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
"""

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            return redirect(url_for('change_email', username=username))
        else:
            return "Invalid credentials. Please try again."
    return render_template_string(login_page)

@app.route('/change-email/<username>', methods=['GET', 'POST'])
def change_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(username)
        
        if not user or user['email'] != old_email:
            return "Old email does not match the records. Please try again."
        
        if user['password'] != confirm_password:
            return "Incorrect password. Please try again."
        
        # Change the email
        user['email'] = new_email
        return f"Email changed successfully to {new_email}."
    
    return render_template_string(change_email_page, username=username)

if __name__ == '__main__':
    app.run(debug=True)