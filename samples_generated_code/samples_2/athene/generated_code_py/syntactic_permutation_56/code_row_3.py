from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

users = {
    'user1': {'password': 'pass1', 'email': 'user1@example.com'}
}

def check_password(username, password):
    return users.get(username, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if username not in users:
            return "User does not exist"

        if not check_password(username, password):
            return "Incorrect password"

        if users[username]['email'] != old_email:
            return "Old email does not match the current email"

        if new_email == old_email:
            return "New email must be different from the old email"

        users[username]['email'] = new_email
        return "Email updated successfully"

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)