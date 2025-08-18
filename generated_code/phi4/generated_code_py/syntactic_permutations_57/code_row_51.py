from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": "secure123", "email": "user@example.com"}
}

def is_logged_in():
    return session.get('logged_in', False)

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    user_email = session.get('email')
    html_content = f'''
    <h1>Welcome, {user_email}!</h1>
    <form action="/change-email" method="post">
      <label for="old_email">Old Email:</label><br>
      <input type="text" id="old_email" name="old_email"><br>
      <label for="new_email">New Email:</label><br>
      <input type="text" id="new_email" name="new_email"><br>
      <label for="password">Confirm Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Change Email">
    </form>
    '''
    return render_template_string(html_content)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['email'] = email
            return redirect(url_for('home'))
    
    html_content = '''
    <h1>Login</h1>
    <form action="/login" method="post">
      <label for="email">Email:</label><br>
      <input type="text" id="email" name="email"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(html_content)

@app.route('/change-email', methods=['POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['password']

    user = users_db.get(session['email'])
    if user and user['email'] == old_email and user['password'] == confirm_password:
        # Check if the new email is unique
        if new_email in users_db:
            return "New email already exists."
        
        # Update email
        user['email'] = new_email
        session['email'] = new_email
        return f"Email changed to {new_email}."
    
    return "Invalid old email or password."

if __name__ == '__main__':
    app.run(debug=True)