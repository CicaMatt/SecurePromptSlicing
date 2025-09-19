from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user database
users_db = {
    "john": {"email": "john@example.com", "password": "123456"},
}

def is_user_logged_in(username):
    return username in users_db

def check_password(username, password):
    return users_db[username]['password'] == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = "john"  # Assume the user is logged in as 'john'
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if not is_user_logged_in(username):
            return "You must be logged in to change your email."

        if users_db[username]['email'] != old_email:
            return "The provided old email does not match the existing one."

        if not check_password(username, confirm_password):
            return "Incorrect password."

        users_db[username]['email'] = new_email
        return "Email changed successfully!"

    # Render form for GET request
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)