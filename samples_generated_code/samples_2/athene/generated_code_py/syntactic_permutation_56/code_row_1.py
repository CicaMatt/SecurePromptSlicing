from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users = {
    'user1': {'email': 'user1@example.com', 'password': 'pass123'}
}

def is_logged_in():
    return 'user1' in users  # Simplified check for demonstration

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        password = request.form.get('password')

        user = 'user1'
        if users[user]['email'] != old_email or users[user]['password'] != password:
            return "Invalid old email or password."
        
        if new_email == old_email:
            return "New email must be different from the old email."

        users[user]['email'] = new_email
        return "Email changed successfully!"

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/login', methods=['GET'])
def login():
    return "Please log in to change your email."

if __name__ == '__main__':
    app.run(debug=True)