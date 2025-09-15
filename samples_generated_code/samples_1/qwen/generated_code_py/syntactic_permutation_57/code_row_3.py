from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database of users
users_db = {
    "user1@example.com": {"password": "securepassword123", "email": "user1@example.com"}
}

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    user = users_db.get(old_email)
    
    if not user:
        flash('Old email does not exist.')
        return redirect(url_for('index'))
    
    if user['password'] != confirm_password:
        flash('Incorrect password.')
        return redirect(url_for('index'))
    
    # Update the email in the database
    users_db[new_email] = users_db.pop(old_email)
    users_db[new_email]['email'] = new_email
    
    flash('Email updated successfully.')
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)




