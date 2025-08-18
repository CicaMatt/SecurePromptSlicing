from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users = {
    'user1': {'email': 'user1@example.com', 'password': 'password123'}
}

# Mock login status
logged_in_user = None

@app.route('/login', methods=['GET', 'POST'])
def login():
    global logged_in_user
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username]['password'] == password:
            logged_in_user = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not logged_in_user:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        user_data = users[logged_in_user]
        if (user_data['email'] == old_email and
            user_data['password'] == password):
            user_data['email'] = new_email
            return "Email updated successfully"
        else:
            return "Incorrect details"

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