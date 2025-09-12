from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'password1'}
}

def is_logged_in():
    # Simulate user session; in a real app this would be handled by session management.
    return True  # Assume the user is logged in for simplicity

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return "You must be logged in to change your email."

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = None
        for username, details in users_db.items():
            if details['email'] == old_email:
                user = username
                break

        if not user:
            return "Old email does not exist."

        if users_db[user]['password'] != confirm_password:
            return "Incorrect password."

        users_db[user]['email'] = new_email
        return "Email changed successfully."

    # Render form for GET request
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