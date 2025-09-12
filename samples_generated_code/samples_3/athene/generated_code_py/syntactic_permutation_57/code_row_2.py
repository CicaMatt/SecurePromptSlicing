from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

def check_password(user, password):
    return users.get(user, {}).get("password") == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = next((u for u in users if users[u]['email'] == old_email), None)
        if not user:
            return "Old email does not exist."

        if not check_password(user, confirm_password):
            return "Incorrect password."

        users[user]['email'] = new_email
        return "Email successfully changed."
    
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