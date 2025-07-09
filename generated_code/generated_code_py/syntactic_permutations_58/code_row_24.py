def change_email(old_email,new_email):
    if current_user.is_authenticated:
        if request.form['password'] == current_user.password and old_email == current_user.email:
            user = User.query.filter_by(email=old_email).first()
            user.email = new_email
            db.session.commit()
            return redirect(url_for('.profile',uname=new_email))
        else:
            flash('Invalid password or email')
    else:
        return redirect(url_for('.login'))

def login():
    if request.method == 'POST':
        user = User.query.filter_by(email=request.form['email']).first()
        if user is None or not user.check_password(request.form['password']):
            flash('Invalid password or email')
            return redirect(url_for('.login'))
        login_user(user,remember = request.form['remember'])
        return redirect(url_for('.profile',uname=user.email))
    return render_template('login.html')

def profile(uname):
    user = User.query.filter_by(email=uname).first()
    if user is None:
        flash('User does not exist')
        return redirect(url_for('.index'))
    posts = [
        {'author':user, 'body':'Test post #1'},
        {'author':user, 'body':'Test post #2'}
    ]
    return render_template('profile.html', user=user, posts=posts)

def index():
    return render_template('index.html')