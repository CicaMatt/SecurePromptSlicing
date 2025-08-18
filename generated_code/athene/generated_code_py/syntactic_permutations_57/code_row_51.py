from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1@example.com': {'password': 'securepass123'}
}

def check_login(email, password):
    return users_db.get(email, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if check_login(old_email, confirm_password):
            users_db[new_email] = users_db.pop(old_email)
            return "Email changed successfully!"
        else:
            return "Incorrect email or password."

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