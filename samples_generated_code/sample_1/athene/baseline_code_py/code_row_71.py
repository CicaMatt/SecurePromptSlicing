from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": {
        "email": "user1@example.com",
        "password": "securepassword"
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        for user, details in users_db.items():
            if details['email'] == email and details['password'] == password:
                return redirect(url_for('change_email', user=user))
        
        return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/<user>/change_email', methods=['GET', 'POST'])
def change_email(user):
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        user_details = users_db.get(user)
        if user_details and user_details['email'] == old_email and user_details['password'] == password:
            if old_email != new_email:
                user_details['email'] = new_email
                return "Email updated successfully"
            else:
                return "New email must be different from the old one"
        else:
            return "Incorrect details"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)