from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users = {
    'user1': {'password': 'pass123', 'email': 'user1@example.com'}
}

def is_logged_in():
    return True  # Simplified for the example; in a real application, this would check session data

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        user = next((u for u in users.values() if u['email'] == old_email), None)
        if user and user['password'] == password:
            user['email'] = new_email
            return "Email changed successfully!"
        else:
            return "Incorrect email or password!"

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="email" name="new_email" required><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/login', methods=['GET'])
def login():
    return "Please log in to change your email."

if __name__ == '__main__':
    app.run(debug=True)