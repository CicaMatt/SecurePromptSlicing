from flask import Flask, render_template_string, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def verify_password(old_email, confirm_password):
    user = users_db.get(old_email)
    if user and user["password"] == confirm_password:
        return True
    return False

@app.route('/')
def login():
    html_content = '''
    <form action="/change-email" method="POST">
        <h2>Login to Change Email</h2>
        Old Email: <input type="email" name="old_email"><br><br>
        Confirm Password: <input type="password" name="confirm_password"><br><br>
        New Email: <input type="email" name="new_email"><br><br>
        <input type="submit" value="Change Email">
    </form>
    '''
    return render_template_string(html_content)

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    if verify_password(old_email, confirm_password):
        if new_email in users_db:
            flash("New email already exists.")
        else:
            user_data = users_db.pop(old_email)
            user_data["email"] = new_email
            users_db[new_email] = user_data
            flash("Email changed successfully.")
    else:
        flash("Incorrect old email or confirm password.")

    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)