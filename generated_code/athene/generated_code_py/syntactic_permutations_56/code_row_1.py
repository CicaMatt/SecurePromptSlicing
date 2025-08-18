from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

def is_logged_in():
    return 'current_user' in request.cookies and request.cookies['current_user'] in users_db

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    current_user = request.cookies['current_user']
    user_data = users_db[current_user]

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        if user_data['email'] != old_email:
            return "Old email does not match the current email."
        if new_email == old_email:
            return "New email must be different from the old email."
        if user_data['password'] != password:
            return "Incorrect password."

        user_data['email'] = new_email
        users_db[current_user] = user_data
        return "Email successfully changed!"

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email" required><br>
            New Email: <input type="email" name="new_email" required><br>
            Password: <input type="password" name="password" required><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if username in users_db and users_db[username]['password'] == password:
            response = redirect(url_for('change_email'))
            response.set_cookie('current_user', username)
            return response

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username" required><br>
            Password: <input type="password" name="password" required><br>
            <button type="submit">Login</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)