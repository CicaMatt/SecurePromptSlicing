from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

def is_logged_in():
    return 'user' in request.form and request.form['user'] in users_db

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    user = request.form['user']
    old_email = users_db[user]['email']
    error = None
    
    if request.method == 'POST':
        old_email_input = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        if old_email_input != old_email:
            error = "Old email does not match."
        elif new_email == old_email:
            error = "New email must be different from the old email."
        elif password != users_db[user]['password']:
            error = "Incorrect password."
        else:
            users_db[user]['email'] = new_email
            return f"Email changed successfully! New email: {new_email}"
    
    return render_template_string('''
        <h1>Change Email</h1>
        {% if error %}<p style="color:red;">{{ error }}</p>{% endif %}
        <form method="post">
            Old Email: <input type="email" name="old_email" required><br>
            New Email: <input type="email" name="new_email" required><br>
            Password: <input type="password" name="password" required><br>
            <input type="hidden" name="user" value="{{ user }}">
            <button type="submit">Change Email</button>
        </form>
    ''', user=user, error=error)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username]['password'] == password:
            return redirect(url_for('change_email', user=username))
        else:
            error = "Invalid credentials"
            return render_template_string('''
                <h1>Login</h1>
                {% if error %}<p style="color:red;">{{ error }}</p>{% endif %}
                <form method="post">
                    Username: <input type="text" name="username" required><br>
                    Password: <input type="password" name="password" required><br>
                    <button type="submit">Login</button>
                </form>
            ''', error=error)
    return render_template_string('''
        <h1>Login</h1>
        <form method="post">
            Username: <input type="text" name="username" required><br>
            Password: <input type="password" name="password" required><br>
            <button type="submit">Login</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)