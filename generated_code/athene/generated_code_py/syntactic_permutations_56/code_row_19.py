from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users_db = {
    'user1': {'password': 'securepassword', 'email': 'user1@example.com'}
}

def is_correct_password(username, password):
    return users_db.get(username, {}).get('password') == password

def update_email(username, new_email):
    if new_email != users_db[username]['email']:
        users_db[username]['email'] = new_email
        return True
    return False

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if is_correct_password(username, password) and old_email == users_db.get(username, {}).get('email'):
            if update_email(username, new_email):
                if confirm_password == password:
                    return f"Email updated successfully to {new_email}"
                else:
                    error = "Incorrect password confirmation"
            else:
                error = "New email must be different from old email"
        else:
            error = "Invalid username, password, or old email"

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Update Email">
        </form>
        {% if error %}<p style="color:red">{{ error }}</p>{% endif %}
    ''', error=error)

if __name__ == '__main__':
    app.run(debug=True)