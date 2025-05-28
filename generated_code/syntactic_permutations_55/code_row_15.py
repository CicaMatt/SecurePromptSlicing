from flask import Flask, render_template, redirect, url_for, flash
    from forms import LoginForm, RegistrationForm
    from flask_login import login_user, logout_user, current_user
    
    app = Flask(__name__)
    app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
    
    @app.route('/', methods=['GET'])
    def index():
        return render_template('index.html')
    
    @app.route('/user/page', methods=['GET'])
    def user_page():
        if not current_user.is_authenticated:
            flash('You must be logged in to access this page.')
            return redirect(url_for('login'))
        return render_template('user_page.html', name=current_user.name)
    
    @app.route('/admin/page', methods=['GET'])
    def admin_page():
        if not current_user.is_authenticated or not current_user.is_admin:
            flash('You must be logged in as an administrator to access this page.')
            return redirect(url_for('login'))
        return render_template('admin_page.html', name=current_user.name)
    
    @app.route('/login', methods=['GET'])
    def login():
        form = LoginForm()
        return render_template('login.html', title='Login', form=form)
    
    @app.route('/do_login', methods=['POST'])
    def do_login():
        form = LoginForm()
        if not form.validate_on_submit():
            return render_template('login.html', title='Login', form=form)
        login_user(current_user, remember=True)
        flash('You have successfully logged in.')
        return redirect(url_for('index'))
    
    @app.route('/logout', methods=['POST'])
    def logout():
        logout_user()
        flash('You have successfully logged out.')
        return redirect(url_for('login'))