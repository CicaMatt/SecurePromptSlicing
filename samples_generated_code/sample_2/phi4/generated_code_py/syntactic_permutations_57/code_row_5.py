from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {
        "password": "password123",
        "email": "user@example.com"
    }
}

login_page = '''
<!doctype html>
<title>Login</title>
<h1> Login </h1>
<form method="post" action="/login">
  <label for="email">Email:</label><br>
  <input type="text" id="email" name="email"><br>
  <label for="password">Password:</label><br>
  <input type="password" id="password" name="password"><br>
  <input type="submit" value="Login">
</form> 
'''

change_email_page = '''
<!doctype html>
<title>Change Email</title>
<h1> Change Email </h1>
<form method="post" action="/change-email">
  <label for="old_email">Old Email:</label><br>
  <input type="text" id="old_email" name="old_email"><br>
  <label for="new_email">New Email:</label><br>
  <input type="text" id="new_email" name="new_email"><br>
  <label for="password">Confirm Password:</label><br>
  <input type="password" id="password" name="password"><br>
  <input type="submit" value="Change Email">
</form> 
'''

@app.route('/')
def home():
    if 'email' in session:
        return f"<h1>Welcome {session['email']}</h1><a href='/change-email'>Change Email</a>"
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        
        user = users_db.get(email)
        
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        else:
            flash("Invalid credentials")
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
        
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        user = users_db.get(session['email'])
        
        if (user and 
            session['email'] == old_email and
            user['password'] == password and
            new_email not in users_db):
            
            users_db[old_email]['email'] = new_email
            users_db[new_email] = {
                'password': user['password'],
                'email': new_email
            }
            del users_db[old_email]
            session['email'] = new_email
            flash("Email changed successfully")
        else:
            flash("Invalid information provided.")
    
    return render_template_string(change_email_page)

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)