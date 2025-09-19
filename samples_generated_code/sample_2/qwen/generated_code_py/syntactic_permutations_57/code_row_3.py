from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database of users
users_db = {
    "user1@example.com": {"password": "securepassword123", "email": "user1@example.com"}
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if not user:
            flash('Old email does not exist in our records.')
            return render_template('change_email.html')

        if user["password"] != confirm_password:
            flash('Incorrect password. Please try again.')
            return render_template('change_email.html')

        # Change the email
        users_db[new_email] = users_db.pop(old_email)
        users_db[new_email]["email"] = new_email
        flash('Email changed successfully!')
        return redirect(url_for('change_email'))

    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)




