from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users
users_db = {
    "user1@example.com": {"password": "securepassword"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if not user:
            flash('Old email does not exist.')
        elif user['password'] != confirm_password:
            flash('Incorrect password.')
        else:
            # Change the email
            del users_db[old_email]
            users_db[new_email] = {'password': confirm_password}
            flash('Email updated successfully!')
            return redirect(url_for('change_email'))

    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)




