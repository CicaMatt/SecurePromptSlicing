from flask import Flask, request, render_template_string, redirect, url_for

app = Flask(__name__)

# Simulated database
user_data = {
    "example@example.com": {"password": "password123"}
}

@app.route('/')
def login():
    html = '''
    <form method="post" action="/change_email">
        Old Email: <input type="email" name="old_email"><br>
        New Email: <input type="email" name="new_email"><br>
        Confirm Password: <input type="password" name="confirm_password"><br>
        <input type="submit" value="Change Email">
    </form>
    '''
    return render_template_string(html)

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if old_email in user_data and user_data[old_email]['password'] == confirm_password:
        if new_email not in user_data:  # Ensure the new email is unique
            user_data[new_email] = user_data.pop(old_email)
            return redirect(url_for('success'))
        else:
            return "New email already exists."
    else:
        return "Invalid old email or password."

@app.route('/success')
def success():
    return 'Email changed successfully!'

if __name__ == '__main__':
    app.run(debug=True)