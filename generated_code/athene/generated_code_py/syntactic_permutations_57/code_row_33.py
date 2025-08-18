from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

def check_login(email, password):
    for user, details in users.items():
        if details['email'] == email and details['password'] == password:
            return True
    return False

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        # Check if the user is logged in
        for user, details in users.items():
            if details['email'] == old_email and details['password'] == confirm_password:
                # Change email
                users[user]['email'] = new_email
                return "Email successfully changed."
        
        return "Incorrect old email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)