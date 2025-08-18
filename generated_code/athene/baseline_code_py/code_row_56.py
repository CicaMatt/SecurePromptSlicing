from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def check_password(user, password):
    return users_db.get(user, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = 'user1'  # Simulate logged-in user
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if check_password(username, password):
            if users_db[username]['email'] == old_email:
                if new_email != old_email:
                    users_db[username]['email'] = new_email
                    return "Email changed successfully!"
                else:
                    return "New email must be different from the old email."
            else:
                return "Old email does not match the current email."
        else:
            return "Incorrect password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)