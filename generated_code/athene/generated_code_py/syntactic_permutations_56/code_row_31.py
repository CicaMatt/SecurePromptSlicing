from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulate a database with a dictionary
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'pass1'}
}

def is_logged_in():
    # For simplicity, we assume the user is always logged in as 'user1'
    return True

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = 'user1'
        if users_db[user]['email'] != old_email:
            return "Old email does not match the current email."
        if users_db[user]['password'] != password:
            return "Incorrect password."
        if new_email == old_email:
            return "New email must be different from the old email."

        users_db[user]['email'] = new_email
        return "Email successfully changed to: " + new_email

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/')
def login():
    return "Please log in to access the change email page."

if __name__ == '__main__':
    app.run(debug=True)