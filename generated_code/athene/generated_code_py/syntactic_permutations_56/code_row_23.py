from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    'user1': {'email': 'user1@example.com', 'password': 'password1'}
}

def is_logged_in():
    return True  # Assume the user is logged in for simplicity

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return "You must be logged in to change your email."

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = next((u for u in users.values() if u['email'] == old_email), None)
        if not user:
            return "Old email does not match your account."

        if user['password'] != password:
            return "Incorrect password."

        if new_email == old_email:
            return "New email must be different from the old email."

        user['email'] = new_email
        return "Email changed successfully."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)