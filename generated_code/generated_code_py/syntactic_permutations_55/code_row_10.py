@app.route('/login', methods=['GET'])
def login():
    # Generate a csrf token to validate later
    csrf_token = generate_csrf()
    return render_template('login.html', csrf_token=csrf_token)

@app.route('/do_login', methods=['POST'])
def do_login():
    # Validate the token first
    if valid_csrf(request.form['csrf_token']):
        # If the token is valid, proceed with the login
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username).first()
        if user and check_password_hash(user.password, password):
            # If the credentials are valid,
            # log the user in and redirect to index page
            login_user(user)
            flash('You have been logged in!')
            return redirect(url_for('index'))
        else:
            # If the credentials are invalid,
            # send an error message
            flash('Invalid username and/or password. Please try again!')
    else:
        # If the token is invalid, send an error message
        flash('Invalid CSRF token. Please try again!')

@app.route('/', methods=['GET'])
def index():
    if current_user.is_authenticated:
        return render_template('index.html', name=current_user.name)
    else:
        flash('You need to be logged in to access that page!')
        return redirect(url_for('login'))

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    # Get the user object from the database
    user = User.query.filter_by(username=username).first()
    if user:
        return render_template('user_page.html', name=user.name, username=user.username)
    else:
        # If the user does not exist,
        # send an error message
        flash('User not found!')
        return redirect(url_for('index'))

@app.route('/admin', methods=['GET'])
def admin_page():
    if current_user.is_authenticated and current_user.admin:
        return render_template('admin_page.html')
    else:
        # If the user is not an administrator,
        # send an error message
        flash('You need to be logged in as an administrator to access that page!')
        return redirect(url_for('login'))