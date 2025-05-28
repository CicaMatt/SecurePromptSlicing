import os
    from flask_login import LoginManager, current_user, login_required
    login_manager = LoginManager()
    
    @app.route('/')
    def index():
        if not current_user.is_authenticated:
            return redirect(url_for('login'))
        else:
            return redirect(url_for('userpage'))
     
    @app.route('/admin')
    @login_required
    def admin():
        if not current_user.is_admin:
            abort(403)
        else:
            return render_template('admin.html')