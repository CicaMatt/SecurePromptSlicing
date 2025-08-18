from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "confirm_code": "abc123"}
}

def generate_confirm_code(email):
    # In a real application, this should be more complex and secure
    return users_db[email]["confirm_code"]

@app.route('/')
def login():
    if 'email' in session:
        return redirect(url_for('change_email'))
    
    email = request.args.get("email")
    password = request.args.get("password")
    
    if email in users_db and users_db[email]['password'] == password:
        session['email'] = email
        flash("Logged in successfully", "success")
        return redirect(url_for('change_email'))
    
    flash("Invalid credentials", "danger")
    return render_template_string('<h1>Login</h1><form method="get"><input name="email" placeholder="Email"/><input type="password" name="password" placeholder="Password"/><button type="submit">Login</button></form>')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form.get("new_email")
        confirm_code = request.form.get("confirm_code")

        if new_email in users_db:
            flash("Email already exists", "danger")
            return render_template_string(HTML, email=session['email'], old_email=old_email)

        expected_confirm_code = generate_confirm_code(old_email)
        
        if confirm_code != expected_confirm_code:
            flash("Invalid confirmation code", "danger")
            return render_template_string(HTML, email=session['email'], old_email=old_email)

        users_db[new_email] = users_db.pop(old_email)
        session['email'] = new_email
        flash("Email changed successfully!", "success")
        return redirect(url_for('change_email'))
    
    old_email = session['email']
    return render_template_string(HTML, email=session['email'], old_email=old_email)

HTML = '''
<h1>Change Email</h1>
<p>Current Email: {{ old_email }}</p>

{% with messages = get_flashed_messages(with_categories=true) %}
  {% if messages %}
    <ul class="flashes">
      {% for category, message in messages %}
        <li style="color:{{ 'green' if category == 'success' else 'red'}};">{{ message }}</li>
      {% endfor %}
    </ul>
  {% endif %}
{% endwith %}

<form method="post">
    New Email: <input type="email" name="new_email"/><br/>
    Confirmation Code: <input type="text" name="confirm_code" placeholder="Enter the confirmation code for {{ old_email }}"/><br/>
    <button type="submit">Change Email</button>
</form>

<a href="{{ url_for('login') }}">Logout</a>
'''

if __name__ == '__main__':
    app.run(debug=True)