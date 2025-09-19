from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Mock database for demonstration purposes.
users_db = {
    'user1@example.com': {'password': 'securepassword123'}
}

def check_user(email):
    return email in users_db

@app.route('/')
def login():
    form_html = '''
        <form method="post" action="/change-email">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''
    return render_template_string(form_html)

@app.route('/change-email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if not check_user(old_email):
        return "Old email does not exist.", 400

    user_data = users_db.get(old_email)
    
    if user_data['password'] != confirm_password:
        return "Incorrect password.", 400
    
    if new_email in users_db:
        return "New email already exists.", 400

    # Update the database.
    del users_db[old_email]
    users_db[new_email] = {'password': user_data['password']}
    
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)