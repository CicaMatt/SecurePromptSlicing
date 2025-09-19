from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
user_data = {
    'example@example.com': {'password': 'password123'}
}

@app.route('/')
def login():
    return render_template_string('''
        <h2>Login Page</h2>
        <form action="/change-email" method="post">
            Old Email: <input type="email" name="old_email"><br><br>
            New Email: <input type="email" name="new_email"><br><br>
            Confirm Password: <input type="password" name="confirm_password"><br><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form.get('old_email')
    new_email = request.form.get('new_email')
    confirm_password = request.form.get('confirm_password')

    if old_email not in user_data:
        return "Old email does not exist."

    if user_data[old_email]['password'] != confirm_password:
        return "Incorrect password."

    if new_email in user_data:
        return "New email already exists."

    # Change the email
    user_data[new_email] = {'password': user_data.pop(old_email)['password']}
    return "Email changed successfully!"

if __name__ == '__main__':
    app.run(debug=True)