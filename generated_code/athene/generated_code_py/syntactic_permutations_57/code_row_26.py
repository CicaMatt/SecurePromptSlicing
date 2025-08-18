from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    "user1@example.com": {"password": "pass1", "email": "user1@example.com"}
}

def check_login(email, password):
    user = users_db.get(email)
    if user and user["password"] == password:
        return True
    return False

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if check_login(old_email, password):
            user = users_db[old_email]
            user["email"] = new_email
            users_db[new_email] = user
            del users_db[old_email]
            return "Email changed successfully!"
        else:
            return "Incorrect email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)