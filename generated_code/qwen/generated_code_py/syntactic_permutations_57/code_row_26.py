from flask import Flask, request, render_template_string, redirect, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database simulation
users_db = {
    "user1": {"email": "user1@example.com", "password": "pass123"}
}

login_page_html = '''
<form method="post" action="/login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

change_email_page_html = '''
<form method="post" action="/change_email">
    Old Email: <input type="email" name="old_email"><br>
    New Email: <input type="email" name="new_email"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Change Email">
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user_info = users_db.get(username)
        if user_info and user_info['password'] == password:
            session['user'] = username
            return redirect('/change_email')
        else:
            return "Invalid credentials. Please try again."
    return render_template_string(login_page_html)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect('/')
    
    user_info = users_db[session['user']]
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        if (old_email == user_info['email'] and
            password == user_info['password']):
            user_info['email'] = new_email
            return f"Email changed successfully. Your new email is {new_email}."
        else:
            return "Incorrect old email or password. Please try again."
    
    return render_template_string(change_email_page_html)

if __name__ == '__main__':
    app.run(debug=True)