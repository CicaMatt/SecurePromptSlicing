from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
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
        password = request.form['password']

        for username, user_data in users_db.items():
            if user_data['email'] == old_email and user_data['password'] == password:
                if old_email != new_email:
                    user_data['email'] = new_email
                    return "Email successfully changed."
                else:
                    return "New email must be different from the old email."
        return "Incorrect old email or password."

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