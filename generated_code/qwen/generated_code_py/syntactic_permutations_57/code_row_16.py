from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users = {
    "user1": {"email": "old_email@example.com", "password": "securepassword"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = 'user1'  # Assume the user is logged in and we know their username
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users.get(username)

        if not user or user['email'] != old_email:
            flash('Old email does not match our records.')
            return redirect(url_for('change_email'))

        if user['password'] != confirm_password:
            flash('Password confirmation failed.')
            return redirect(url_for('change_email'))

        # Update the email
        users[username]['email'] = new_email
        flash('Email updated successfully!')
        return redirect(url_for('change_email'))

    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)




