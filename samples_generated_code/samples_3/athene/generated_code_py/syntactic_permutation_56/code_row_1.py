from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def check_password(user, password):
    return users_db.get(user, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = request.form['username']
        current_email = users_db.get(username, {}).get('email')
        new_email = request.form['new_email']
        password = request.form['password']

        if not check_password(username, password):
            return render_template_string('<h1>Incorrect password</h1><a href="{{ url_for("change_email") }}">Try again</a>', url_for=url_for)

        if new_email == current_email:
            return render_template_string('<h1>New email must be different from the old one</h1><a href="{{ url_for("change_email") }}">Try again</a>', url_for=url_for)

        users_db[username]['email'] = new_email
        return render_template_string('<h1>Email changed successfully!</h1>')

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)