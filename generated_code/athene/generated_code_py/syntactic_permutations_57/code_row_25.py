from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1@example.com': {'password': 'securepassword', 'email': 'user1@example.com'}
}

def is_logged_in():
    # For simplicity, we assume the user is logged in if they provide a valid old email and password.
    return True

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return "You must be logged in to change your email.", 401
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        confirm_password = request.form.get('confirm_password')
        new_email = request.form.get('new_email')

        user = users_db.get(old_email)
        if not user or user['password'] != confirm_password:
            return "Invalid old email or password.", 403

        user['email'] = new_email
        users_db[new_email] = users_db.pop(old_email)
        return "Email changed successfully."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            New Email: <input type="email" name="new_email"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)