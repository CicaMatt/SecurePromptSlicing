from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1@example.com': {'password': 'secure123', 'email': 'user1@example.com'}
}

def is_logged_in():
    # For simplicity, we assume the user is always logged in for this demo.
    return True

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return "You must be logged in to change your email."

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        if not user:
            return "Old email does not exist."
        
        if user['password'] != confirm_password:
            return "Incorrect password."

        user['email'] = new_email
        users_db[new_email] = user
        del users_db[old_email]

        return f"Email changed successfully to {new_email}."

    # HTML form for changing email
    html_form = '''
    <form method="post">
        Old Email: <input type="email" name="old_email" required><br>
        New Email: <input type="email" name="new_email" required><br>
        Confirm Password: <input type="password" name="confirm_password" required><br>
        <input type="submit" value="Change Email">
    </form>
    '''
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)