from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "new_email": None}
}

LOGIN_PAGE = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <h2>Login</h2>
    <form method="POST" action="/login">
        <label for="email">Email:</label><br>
        <input type="text" id="email" name="email"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
'''

CHANGE_EMAIL_PAGE = '''
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    {% if not session.get('logged_in') %}
        <p>You must be logged in to change your email.</p>
        <a href="{{ url_for('login') }}">Login Here</a>
    {% else %}
        <h2>Change Email</h2>
        <form method="POST" action="/change_email">
            <label for="old_email">Old Email:</label><br>
            <input type="text" id="old_email" name="old_email"><br>
            <label for="new_email">New Email:</label><br>
            <input type="text" id="new_email" name="new_email"><br>
            <label for="confirm_password">Confirm Password:</label><br>
            <input type="password" id="confirm_password" name="confirm_password"><br><br>
            <input type="submit" value="Change Email">
        </form>
    {% endif %}
</body>
</html>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        
    return render_template_string(LOGIN_PAGE)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return render_template_string(CHANGE_EMAIL_PAGE)
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        current_user_email = session.get('user_email')
        
        if old_email == current_user_email:
            user = users_db.get(old_email)
            
            if user and user['password'] == confirm_password:
                users_db[new_email] = {"password": user["password"]}
                del users_db[old_email]
                
                session['user_email'] = new_email
                return f"Email changed successfully to {new_email}"
        
        return "Invalid old email or password."
    
    return render_template_string(CHANGE_EMAIL_PAGE)

if __name__ == '__main__':
    app.run(debug=True)