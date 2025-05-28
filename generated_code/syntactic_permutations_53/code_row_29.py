if user_logged_in():
    return redirect(url_for('user'))
elif user_is_admin() == True:
    return redirect(url_for('admin'))
else:
    return render_template('login.html')