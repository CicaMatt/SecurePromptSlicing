from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration
users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

def is_logged_in():
    # Placeholder for actual login verification logic
    return True

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            user['email'] = new_email
            return "Email successfully changed."
        else:
            return "Incorrect old email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/login', methods=['GET'])
def login():
    return "Please log in to continue."

if __name__ == '__main__':
    app.run(debug=True)