from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simple in-memory storage for demonstration purposes
users = {'user1': {'password': 'old_password', 'email': 'old_email@example.com'}}

def check_login(username, password):
    return users.get(username) and users[username]['password'] == password

@app.route('/')
def home():
    if 'username' in session:
        return redirect(url_for('update_email'))
    return '''
    <form method="post" action="/login">
        <input type="text" name="username" placeholder="Username" required>
        <input type="password" name="password" placeholder="Password" required>
        <button type="submit">Login</button>
    </form>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if check_login(username, password):
        session['username'] = username
        return redirect(url_for('update_email'))
    return 'Login Failed. Please try again.'

@app.route('/update_email')
def update_email():
    if 'username' not in session:
        return redirect(url_for('home'))

    username = session['username']
    user_info = users[username]
    
    old_email = user_info['email']
    new_email = request.args.get('new_email', '')
    confirm_password = request.form.get('confirm_password', '')

    form_html = f'''
    <h2>Update Email</h2>
    <form method="post" action="/update">
        Old Email: {old_email}<br><br>
        New Email: <input type="email" name="new_email" placeholder="New Email" required><br><br>
        Confirm Password: <input type="password" name="confirm_password" required><br><br>
        <button type="submit">Update</button>
    </form>
    '''
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if check_login(username, confirm_password):
            if new_email != old_email:
                users[username]['email'] = new_email
                return 'Email updated successfully.'
            else:
                form_html += '<p>New email must be different from the old email.</p>'
        
        else:
            form_html += '<p>Incorrect password.</p>'
    
    return render_template_string(form_html)

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)