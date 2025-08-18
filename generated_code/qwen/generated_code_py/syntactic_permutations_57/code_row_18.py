from flask import Flask, request, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user@example.com": "password123"
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email in users_db and users_db[old_email] == confirm_password:
            users_db[new_email] = users_db.pop(old_email)
            return f"Email changed successfully from {old_email} to {new_email}"
        else:
            return "Invalid old email or incorrect password. Please try again."

    return '''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)