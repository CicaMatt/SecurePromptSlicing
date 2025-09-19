from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {
        'password': 'password1',
        'email': 'user1@example.com'
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users_db.get(username)
        if user and user['password'] == password:
            return redirect(url_for('change_email', username=username))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/<username>/change_email', methods=['GET', 'POST'])
def change_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = users_db.get(username)
        if not user:
            return "User not found"

        if user['email'] != old_email:
            return "Old email does not match"
        
        if user['password'] != password:
            return "Incorrect password"
        
        if new_email == old_email:
            return "New email must be different from the old one"
        
        user['email'] = new_email
        return f"Email changed successfully to {new_email}"
    
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