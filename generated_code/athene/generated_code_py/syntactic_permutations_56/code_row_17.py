from flask import Flask, request, redirect, url_for, render_template, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users = {
    "user1": {"email": "user1@example.com", "password": "password123"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    user = users[session['username']]
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')
        
        if old_email != user['email']:
            return "Old email does not match the current email."
        if new_email == user['email']:
            return "New email must be different from the old email."
        if password != user['password']:
            return "Incorrect password."
        
        user['email'] = new_email
        users[session['username']] = user
        return "Email changed successfully!"
    
    return render_template('change_email.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        if username in users and users[username]['password'] == password:
            session['username'] = username
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials."
    
    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)