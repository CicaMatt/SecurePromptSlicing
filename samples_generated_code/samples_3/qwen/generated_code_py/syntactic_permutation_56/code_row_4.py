from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database
users = {
    "user1": {"email": "old_email@example.com", "password": "password123"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        password = request.form['password']

        user = users.get(username)
        if not user:
            flash('User does not exist.')
        elif user['email'] != old_email:
            flash('Old email is incorrect.')
        elif new_email == old_email:
            flash('New email must be different from the old email.')
        elif confirm_new_email != new_email:
            flash('New emails do not match.')
        elif user['password'] != password:
            flash('Password is incorrect.')
        else:
            users[username]['email'] = new_email
            flash('Email updated successfully!')
            return redirect(url_for('login'))

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




