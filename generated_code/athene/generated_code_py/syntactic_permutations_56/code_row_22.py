from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'password': 'pass1', 'email': 'user1@example.com'}
}

def check_password(username, password):
    return users_db.get(username, {}).get('password') == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = request.form['username']
        old_email = users_db.get(username, {}).get('email')
        new_email = request.form['new_email']
        password = request.form['password']

        # Check if user is logged in and password is correct
        if check_password(username, password) and new_email != old_email:
            users_db[username]['email'] = new_email
            return f"Email changed successfully to {new_email}"
        else:
            return "Invalid credentials or email not changed"
    
    # Render form for GET request
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