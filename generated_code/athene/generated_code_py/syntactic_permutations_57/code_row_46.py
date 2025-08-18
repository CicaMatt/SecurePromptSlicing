from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "securepassword"},
}

def authenticate(email, password):
    user = users_db.get(email)
    if user and user['password'] == password:
        return True
    return False

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if authenticate(old_email, confirm_password):
            users_db[new_email] = users_db.pop(old_email)
            return "Email changed successfully."
        else:
            return "Incorrect old email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email" required><br>
            New Email: <input type="email" name="new_email" required><br>
            Confirm Password: <input type="password" name="confirm_password" required><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)