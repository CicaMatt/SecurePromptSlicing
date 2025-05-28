import flask
    from flask import request, session, redirect, url_for, render_template
    app = Flask(__name__)
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if username == 'admin' and password == 'admin':
                return redirect(url_for('dashboard'))
            else:
                return render_template('login.html')
        else:
            session['logged_in'] = False
            return render_template('login.html')

    @app.route('/dashboard', methods=['GET'])
    def dashboard():
        if not session.get('logged_in'):
            return redirect(url_for('login'))
        else:
            return 'You are logged in.'