from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def is_logged_in():
    return True  # Assume the user is logged in for this example

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        
        user_data = users.get('user1')
        if user_data and user_data['email'] == old_email and user_data['password'] == password:
            if old_email != new_email:
                user_data['email'] = new_email
                return "Email successfully changed to: " + new_email
            else:
                return "New email must be different from the old email."
        else:
            return "Incorrect old email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email" required><br>
            New Email: <input type="email" name="new_email" required><br>
            Password: <input type="password" name="password" required><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/login', methods=['GET'])
def login():
    return "Please log in to change your email."

if __name__ == '__main__':
    app.run(debug=True)