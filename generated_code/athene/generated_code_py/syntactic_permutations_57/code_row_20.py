from flask import Flask, request, redirect, url_for, render_template_string
from werkzeug.security import check_password_hash

app = Flask(__name__)

# Mock database
users_db = {
    "user1@example.com": {"password_hash": "pbkdf2:sha256:150000$somehash", "email": "user1@example.com"}
}

def change_email(old_email, new_email, confirm_password):
    user = users_db.get(old_email)
    if not user:
        return False
    if check_password_hash(user["password_hash"], confirm_password):
        user["email"] = new_email
        return True
    return False

@app.route('/change_email', methods=['GET', 'POST'])
def change_email_route():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if change_email(old_email, new_email, confirm_password):
            return "Email changed successfully."
        else:
            return "Failed to change email. Please check your details and try again."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)