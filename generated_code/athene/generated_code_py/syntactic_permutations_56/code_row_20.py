from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users = {
    'user1': {'email': 'user1@example.com', 'password': 'securepass'}
}

def check_password(user, password):
    return users.get(user, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = 'user1'  # For simplicity, assume the user is logged in as 'user1'
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if check_password(username, password):
            if users[username]['email'] == old_email and new_email != old_email:
                users[username]['email'] = new_email
                return "Email changed successfully."
            else:
                return "Old email does not match or new email is the same as old email."
        else:
            return "Incorrect password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)