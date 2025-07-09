from flask import render_template

@app.route('/<username>')
def show_user_profile(username):
    return render_template('user/<username>.html', username=username)