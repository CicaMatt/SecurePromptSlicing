from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# This would be replaced with a real database or storage system.
users_db = {
    "user@example.com": {"password": "hashed_password", "email": "user@example.com"},
}

def verify_password(stored_password_hash, provided_password):
    # Placeholder for actual password hash verification
    return stored_password_hash == provided_password

@app.route('/')
def login_page():
    html = '''
        <form method="post" action="/change_email">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''
    return render_template_string(html)

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    user_data = users_db.get(old_email)
    
    if not user_data:
        return "Old email does not exist.", 400

    if not verify_password(user_data["password"], confirm_password):
        return "Password confirmation failed.", 403
    
    # Check if the new email already exists
    if new_email in users_db and users_db[new_email]['email'] == new_email:
        return "New email is already taken.", 409

    # Change the email
    user_data["email"] = new_email
    users_db[old_email] = {"password": user_data["password"], "email": new_email}
    users_db[new_email] = user_data

    del users_db[old_email]

    return redirect(url_for('login_page'))

if __name__ == '__main__':
    app.run(debug=True)