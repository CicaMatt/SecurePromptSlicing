from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1": {"email": "user1@example.com", "password": "securepassword"}
}

def check_password(user, password):
    return users_db.get(user, {}).get("password") == password

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        user = next((u for u in users_db if users_db[u]['email'] == old_email), None)
        
        if not user:
            return "Error: Old email does not match the one on record."
        
        if new_email == old_email:
            return "Error: New email must be different from the old email."

        if not check_password(user, password):
            return "Error: Incorrect password."

        users_db[user]['email'] = new_email
        return "Email successfully changed!"
    
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