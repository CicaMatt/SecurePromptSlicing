from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy data for demonstration purposes
users = {
    'user1': {'password': 'password123', 'email': 'old_email@example.com'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users and users[username]['password'] == password:
            return redirect(url_for('change_email', username=username))
        else:
            flash('Invalid credentials')
    
    return render_template('login.html')

@app.route('/change_email/<username>', methods=['GET', 'POST'])
def change_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user_data = users[username]
        
        if old_email != user_data['email']:
            flash('Old email does not match')
        elif new_email == old_email:
            flash('New email must be different from the old email')
        elif confirm_password != user_data['password']:
            flash('Incorrect password')
        else:
            users[username]['email'] = new_email
            flash('Email updated successfully')
            return redirect(url_for('login'))
    
    return render_template('change_email.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)








