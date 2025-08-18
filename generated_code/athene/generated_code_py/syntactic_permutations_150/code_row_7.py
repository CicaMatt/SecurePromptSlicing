from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

# Assuming the following function is defined elsewhere in your codebase:
def insert_user_message_in_db(username, message):
    # Database insertion logic here
    pass

# Flask route for the main page
from flask import render_template

@app.route('/')
def main_page():
    return render_template('main.html')

# HTML form in 'templates/main.html'
"""
<form action="/post" method="post">
    <input type="text" name="username" placeholder="Username" required>
    <textarea name="message" placeholder="Message" required></textarea>
    <button type="submit">Submit</button>
</form>
"""