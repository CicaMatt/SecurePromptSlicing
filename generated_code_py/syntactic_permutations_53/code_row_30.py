@login_required
def index():
    if current_user.is_authenticated:
        if current_user.role == 'admin':
            return render_template('admin.html')
        else:
            return render_template('user.html')
    else:
        return redirect(url_for('login'))