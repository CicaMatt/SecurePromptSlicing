from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users = {
    "user1": {"password": "pass123", "email": "old@example.com"}
}

login_page_html = '''
<form method="post">
  Username: <input type="text" name="username"><br>
  Password: <input type="password" name="password"><br>
  <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
{% if not session.get('logged_in') %}
    <p>You must be logged in to change your email.</p>
{% else %}
    <form method="post">
      Old Email: <input type="text" name="old_email"><br>
      New Email: <input type="text" name="new_email"><br>
      Confirm Password: <input type="password" name="confirm_password"><br>
      <input type="submit" value="Change Email">
    </form>
{% endif %}
'''

@app.route('/')
def index():
    return login_page_html

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users and users[username]['password'] == password:
        session['logged_in'] = True
        session['user_email'] = users[username]['email']
        return redirect(url_for('change_email'))
        
    return login_page_html

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if session.get('logged_in') and session.get('user_email') == old_email:
            user_key = [key for key, value in users.items() if value["email"] == old_email][0]
            if users[user_key]['password'] == confirm_password and new_email != old_email:
                users[user_key]['email'] = new_email
                session['user_email'] = new_email
                return f"Email changed to {new_email}"
            
        return "Invalid input or credentials"

    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)