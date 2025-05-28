from flask import Flask, session, request, redirect, url_for, render_template
    app = Flask(__name__)

    # Login route
    @app.route('/login')
    def login():
        if 'user' in session:
            return redirect(url_for('user'))
        return render_template("login.html")

    # User route
    @app.route('/user')
    def user():
        if not 'user' in session:
            return redirect(url_for('login'))
        return render_template("user.html", name=session['user'])

    # Admin route
    @app.route('/admin')
    def admin():
        if not 'user' in session:
            return redirect(url_for('login'))
        if not session['user'] == "admin":
            return render_template("error.html", message="You are not authorized to view this page.")
        return render_template("admin.html")

    # Logout route
    @app.route('/logout')
    def logout():
        session.pop('user', None)
        return redirect(url_for('login'))

    if __name__ == "__main__":
        app.secret_key = 'super secret key'
        app.run(host='0.0.0.0')