from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123", "confirmed_password": "password123"}
}

EMAIL_CHANGE_TEMPLATE = '''
<!doctype html>
<title>Change Email</title>
<h2>Change Email</h2>
{% if error %}
  <p style="color: red;">{{ error }}</p>
{% endif %}
<form method=post>
  Old Email:<br><input type=text name=old_email><br>
  New Email:<br><input type=text name=new_email><br>
  Confirm Password:<br><input type=password name=confirm_password><br>
  <input type=submit value=Change>Email>
</form>
'''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in_email'] = email
            return redirect(url_for('change_email'))
        
        return "Invalid credentials", 401
    
    return '''
    <form method="post">
      Email:<br><input type="text" name="email"><br>
      Password:<br><input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in_email' not in session:
        return redirect(url_for('login'))

    logged_in_email = session['logged_in_email']
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(logged_in_email)
        
        if not user:
            return "User does not exist", 404
        
        if old_email != logged_in_email or user['password'] != confirm_password:
            return render_template_string(EMAIL_CHANGE_TEMPLATE, error="Invalid credentials")
        
        if new_email in users_db:
            return render_template_string(EMAIL_CHANGE_TEMPLATE, error="New email already exists")

        # Change the email
        del users_db[logged_in_email]
        users_db[new_email] = {"password": user['password'], "confirmed_password": confirm_password}
        
        session['logged_in_email'] = new_email
        
        return f"Email changed to {new_email} successfully"
    
    return render_template_string(EMAIL_CHANGE_TEMPLATE)

@app.route('/logout')
def logout():
    session.pop('logged_in_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)