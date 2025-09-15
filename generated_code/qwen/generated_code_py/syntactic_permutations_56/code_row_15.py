from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    "user1": {"email": "old_email@example.com", "password": "secure_password"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_new_email = request.form['confirm_new_email']
        password = request.form['password']

        user = users_db.get(username)
        if user and user["email"] == old_email and user["password"] == password:
            if new_email != old_email:
                if new_email == confirm_new_email:
                    user["email"] = new_email
                    flash('Email updated successfully!')
                    return redirect(url_for('login'))
                else:
                    flash('New email and confirm email do not match.')
            else:
                flash('New email must be different from the old email.')
        else:
            flash('Invalid username, password, or old email.')

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




