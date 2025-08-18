from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1': {'password': 'pass1', 'email': 'user1@example.com'}
}

def is_logged_in(username):
    return username in users_db

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        username = request.form['username']
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if not is_logged_in(username):
            return "You must be logged in to change your email."

        user = users_db[username]

        if user['email'] != old_email:
            return "Old email does not match the current email."
        
        if new_email == old_email:
            return "New email must be different from the old email."
        
        if user['password'] != password:
            return "Incorrect password."

        user['email'] = new_email
        return redirect(url_for('change_email', success=True))

    success = request.args.get('success')
    template = '''
    {% if success %}
        <h1>Email successfully changed!</h1>
    {% else %}
        <form method="post">
            Username: <input type="text" name="username"><br>
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    {% endif %}
    '''
    return render_template_string(template, success=success)

if __name__ == '__main__':
    app.run(debug=True)