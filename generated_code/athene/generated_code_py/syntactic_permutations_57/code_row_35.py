from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "john.doe@example.com": {"password": "secure123", "email": "john.doe@example.com"}
}

def is_logged_in():
    return 'user' in request.form and request.form['user'] in users_db

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return render_template_string('<h1>You must be logged in to change your email.</h1>'), 403
    
    user = request.form['user']
    old_email = users_db[user]['email']
    
    if request.method == 'POST':
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')
        
        if not new_email or not confirm_password:
            return render_template_string('<h1>Please provide both new email and confirm password.</h1>'), 400
        
        if users_db[user]['password'] != confirm_password:
            return render_template_string('<h1>Incorrect confirm password.</h1>'), 400
        
        users_db[user]['email'] = new_email
        return render_template_string(f'<h1>Email changed successfully. New email: {new_email}</h1>')
    
    return render_template_string('''
        <form method="post">
            <label for="new_email">New Email:</label>
            <input type="email" id="new_email" name="new_email" required><br>
            <label for="confirm_password">Confirm Password:</label>
            <input type="password" id="confirm_password" name="confirm_password" required><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)