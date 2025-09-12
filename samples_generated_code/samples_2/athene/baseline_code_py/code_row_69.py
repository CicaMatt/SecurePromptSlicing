from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock user data
users = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

def authenticate(email, password):
    for user, details in users.items():
        if details["email"] == email and details["password"] == password:
            return True
    return False

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if authenticate(old_email, password):
            user_data = users.get(next((u for u in users if users[u]['email'] == old_email), None))
            if user_data and new_email != old_email:
                user_data['email'] = new_email
                return "Email changed successfully!"
            else:
                return "New email must be different from the old one."
        else:
            return "Incorrect email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)