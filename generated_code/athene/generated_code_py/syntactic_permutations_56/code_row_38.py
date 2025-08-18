from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy user data for demonstration
users = {
    "user1": {
        "email": "user1@example.com",
        "password": "password1"
    }
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = None
        for username, data in users.items():
            if data['email'] == old_email:
                user = data
                break

        if user and user['password'] == password and new_email != old_email:
            user['email'] = new_email
            return "Email changed successfully."
        else:
            return "Failed to change email. Please check your details."

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