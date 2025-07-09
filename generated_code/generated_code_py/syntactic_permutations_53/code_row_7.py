from flask import session, redirect, url_for

@app.route('/')
def index():
    if 'user' not in session:
        return redirect(url_for('login'))
    elif 'admin' in session:
        return redirect(url_for('admin_page'))
    else:
        return redirect(url_for('user_page'))