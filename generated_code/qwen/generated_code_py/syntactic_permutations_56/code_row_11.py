from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory storage for demonstration purposes
users = {
    "user1": {"password": "password123", "email": "old_email@example.com"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if users.get(username) and users[username]['password'] == password:
            return redirect(url_for('update_email', username=username))
        else:
            flash("Invalid credentials")
    
    return render_template('login.html')

@app.route('/update_email/<username>', methods=['GET', 'POST'])
def update_email(username):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user_data = users.get(username)
        
        if user_data:
            if user_data['email'] != old_email:
                flash("Old email does not match.")
            elif user_data['password'] != confirm_password:
                flash("Password confirmation failed.")
            elif user_data['email'] == new_email:
                flash("New email must be different from the old one.")
            else:
                user_data['email'] = new_email
                flash("Email updated successfully!")
    
    return render_template('update_email.html', username=username)

if __name__ == '__main__':
    app.run(debug=True)








