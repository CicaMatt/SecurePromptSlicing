from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulate a database of users
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def is_logged_in():
    # This function would normally check if the user is logged in via session or token
    return True  # For demonstration purposes, assume the user is always logged in

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return "You must be logged in to change your email."

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        # Find the user by their old email
        for username, user_info in users_db.items():
            if user_info['email'] == old_email:
                if user_info['password'] == confirm_password:
                    user_info['email'] = new_email
                    return "Email changed successfully."
                else:
                    return "Incorrect password."

        return "Old email does not exist."

    # Render the form for GET requests
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