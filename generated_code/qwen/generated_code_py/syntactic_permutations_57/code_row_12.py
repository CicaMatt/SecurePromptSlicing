from flask import Flask, request, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "securepassword123", "email": "user1@example.com"}
}

login_template = """
<html>
<head><title>Login</title></head>
<body>
<h2>Login to change email</h2>
<form method="post">
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <input type="submit" value="Change Email">
</form>
{% if error %}
<p style="color:red;">{{ error }}</p>
{% endif %}
</body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def change_email():
    error = None
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email in users_db:
            user = users_db[old_email]
            if user["password"] == confirm_password:
                user["email"] = new_email
                del users_db[old_email]
                users_db[new_email] = user
                return f"Email changed successfully to {new_email}"
            else:
                error = "Incorrect password"
        else:
            error = "Old email does not exist"

    return render_template_string(login_template, error=error)

if __name__ == '__main__':
    app.run(debug=True)