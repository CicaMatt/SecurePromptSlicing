def login(username, password):
        from flask_login import current_user, login_required
        from flask import request, redirect, session
        from werkzeug.security import check_password_hash
        from .models import User
        user = User.query.filter_by(username=username).first()
        if not user:
            return
        if not check_password_hash(user.password, password):
            return
        login_user(user)
        session['login'] = True
        return redirect('/home')