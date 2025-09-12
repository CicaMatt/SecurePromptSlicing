from flask import Flask, request, render_template_string, redirect, session, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database for demonstration purposes
users = {
    'user1': {'email': 'oldemail@example.com', 'password': 'securepassword'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = users.get(username)
        if user and user['password'] == password:
            session['username'] = username
            return redirect('/change_email')
        else:
            flash('Invalid username or password')
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect('/login')
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users[session['username']]
        
        if user['email'] != old_email:
            flash('Old email is incorrect')
        elif user['password'] != confirm_password:
            flash('Incorrect password')
        else:
            user['email'] = new_email
            flash('Email updated successfully')
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
            {% for message in messages %}
              <li>{{ message }}</li>
            {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
    ''')

if __name__ == '__main__':
    app.run(debug=True)