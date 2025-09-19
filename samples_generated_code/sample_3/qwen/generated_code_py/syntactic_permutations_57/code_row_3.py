from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

@app.route('/', methods=['GET', 'POST'])
def login():
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
            # Update the email in the mock database
            del users_db[old_email]
            users_db[new_email] = {"password": confirm_password, "email": new_email}
            flash('Email updated successfully.')

    return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)




