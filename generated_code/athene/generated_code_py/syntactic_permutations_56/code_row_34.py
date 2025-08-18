from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

users = {
    'user1': {'password': 'pass1', 'email': 'user1@example.com'}
}

def is_password_correct(username, password):
    return users.get(username, {}).get('password') == password

def update_email(username, old_email, new_email, password):
    if not is_password_correct(username, password):
        return False
    if users[username]['email'] != old_email:
        return False
    if new_email == old_email:
        return False
    users[username]['email'] = new_email
    return True

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if is_password_correct(username, password):
            return redirect(url_for('update'))
        else:
            error = 'Invalid credentials. Please try again.'
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
        {{ error }}
    ''', error=error)

@app.route('/update', methods=['GET', 'POST'])
def update():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        username = request.form['username']
        if update_email(username, old_email, new_email, password):
            return f"Email updated successfully to {new_email}"
        else:
            error = "Failed to update email. Please check your details."
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Update Email">
        </form>
        {{ error }}
    ''', error=request.args.get('error'))

if __name__ == '__main__':
    app.run(debug=True)