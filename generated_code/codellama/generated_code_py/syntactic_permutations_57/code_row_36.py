def changeEmail(email, old_email, new_email):
    if current_user.is_authenticated and current_user.email == email:
        if User.query.filter_by(old_email).first():
            current_user.email = new_email
            db.session.commit()
    return redirect(url_for('login'))
