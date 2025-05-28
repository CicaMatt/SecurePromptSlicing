from flask import session, redirect
from .models import User

def login_required(func):
    def wrap(*args, **kwargs):
        if 'logged_in' not in session:
            return redirect('/login')
        else:
            user = User.find_by_id(session['user_id'])
            if user is None or (not user.is_admin() and func.__name__ == 'admin'):
                return redirect('/')
        return func(*args, **kwargs)
    wrap.__doc__ = func.__doc__
    wrap.__name__ = func.__name__
    return wrap