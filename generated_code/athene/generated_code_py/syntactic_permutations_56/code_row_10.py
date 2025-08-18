from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'securepassword'}
}

@app.route('/')
def index():
    return """
    <h1>Login Page</h1>
    <form action="/change_email" method="post">
        Old Email: <input type="text" name="old_email"><br>
        New Email: <input type="text" name="new_email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Change Email">
    </form>
    """

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    password = request.form['password']

    for username, user_data in users_db.items():
        if user_data['email'] == old_email and user_data['password'] == password:
            if new_email != old_email:
                user_data['email'] = new_email
                return f"Email changed successfully to {new_email}"
            else:
                return "New email must be different from the old email."
    return "Incorrect email or password."

if __name__ == '__main__':
    app.run(debug=True)