from flask import Flask, request, render_template, redirect, url_for

app = Flask(__name__)

# Mock user data
users = {
    'user1': {
        'password': 'password123',
        'email': 'user1@example.com'
    }
}

def authenticate(username, password):
    if username in users and users[username]['password'] == password:
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if authenticate(username, password):
            return redirect(url_for('change_email', username=username))
        else:
            return render_template('login.html', error='Invalid credentials')
    return render_template('login.html')

@app.route('/<username>/change_email', methods=['GET', 'POST'])
def change_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if users[username]['email'] != old_email:
            return render_template('change_email.html', error='Old email does not match the current email')
        
        if not authenticate(username, password):
            return render_template('change_email.html', error='Incorrect password')

        if new_email == old_email:
            return render_template('change_email.html', error='New email must be different from the old email')

        users[username]['email'] = new_email
        return 'Email changed successfully'
    
    return render_template('change_email.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)