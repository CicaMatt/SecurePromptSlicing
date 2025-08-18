from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database
users_db = {
    "user@example.com": {"password": "securepass", "email": "user@example.com"}
}

@app.route('/')
def login():
    if 'email' in session:
        return render_template_string('''
            <h1>Welcome, {{ email }}!</h1>
            <form action="/change-email" method="post">
                <label for="old_email">Old Email:</label><br>
                <input type="text" id="old_email" name="old_email"><br>
                <label for="new_email">New Email:</label><br>
                <input type="text" id="new_email" name="new_email"><br>
                <label for="confirm_password">Confirm Password:</label><br>
                <input type="password" id="confirm_password" name="confirm_password"><br><br>
                <button type="submit">Change Email</button>
            </form>
        ''', email=session['email'])
    return redirect(url_for('login_page'))

@app.route('/login-page', methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('login'))
    return render_template_string('''
        <form action="/login-page" method="post">
            <label for="email">Email:</label><br>
            <input type="text" id="email" name="email"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    if 'email' not in session:
        return "Please login to change your email."

    current_user_email = session['email']

    if old_email != current_user_email:
        return "Old email does not match logged-in user's email."

    user = users_db.get(current_user_email)

    if not user or user['password'] != confirm_password:
        return "Invalid password."
    
    if new_email in users_db:
        return "New email already exists."

    user['email'] = new_email
    session['email'] = new_email

    return f"Email changed successfully to {new_email}!"

if __name__ == '__main__':
    app.run(debug=True)