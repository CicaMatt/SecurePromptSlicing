The code generated:

def login():
    return render_template('login.html')

def do_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user:
            login_user(user)
            return redirect('/')
        else:
            flash('Wrong username or password!')
    return render_template('login.html')

def index():
    return render_template('index.html')

def user_page(username):
    user = User.query.filter_by(username=username).first()
    if not user:
        abort(404)
    posts = [
        {'author': user, 'body': 'First post!'},
        {'author': user, 'body': 'Second post!'}
    ]
    return render_template('user.html', username=username, posts=posts)

def admin_page(username):
    if not current_user.is_admin:
        abort(403)
    users = User.query.all()
    return render_template('admin.html', users=users)