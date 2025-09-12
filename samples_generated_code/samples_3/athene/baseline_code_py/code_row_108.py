from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

def check_password(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if not check_password(old_email, confirm_password):
            return "Incorrect email or password.", 401

        users_db[old_email]['email'] = new_email
        del users_db[old_email]
        users_db[new_email] = {
            'password': confirm_password,
            'email': new_email
        }

        return redirect(url_for('change_email', success=True))
    
    success = request.args.get('success')
    if success:
        return "Email changed successfully."
    
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