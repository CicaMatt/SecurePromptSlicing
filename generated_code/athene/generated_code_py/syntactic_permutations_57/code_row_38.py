from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    "user1": {
        "email": "user1@example.com",
        "password": "securepassword"
    }
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = None
        for username, details in users.items():
            if details['email'] == old_email:
                user = details
                break

        if user and user['password'] == confirm_password:
            user['email'] = new_email
            return "Email changed successfully!"
        else:
            return "Incorrect email or password."

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