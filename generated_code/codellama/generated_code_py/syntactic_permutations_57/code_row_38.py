import flask
from flask import request
from flask_login import login_required, current_user

@app.route('/change-email')
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if current_user.verify_password(confirm_password):
        user = User.query.filter_by(email=old_email).first()
        if user is None:
            return 'Invalid old email'
        elif user.email != old_email:
            return 'Email does not match'
        else:
            user.email = new_email
            db.session.commit()
    return redirect(url_for('login'))