from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
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
        user = next((u for u in users.values() if u["email"] == email), None)
        if user and user["password"] == password:
            return redirect(url_for('change_email', email=email))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    current_email = request.args.get('email')
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = users.get(current_email)
        if not user:
            return "User not found"
        
        if old_email != current_email or user["password"] != password:
            return "Old email or password is incorrect"

        if new_email == current_email:
            return "New email must be different from the old email"

        user["email"] = new_email
        return f"Email changed successfully to {new_email}"
    
    return render_template_string(f'''
        <form method="post">
            Old Email: <input type="text" name="old_email" value="{current_email}" readonly><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)