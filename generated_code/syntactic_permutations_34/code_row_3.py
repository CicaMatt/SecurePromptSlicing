from flask import Flask, request, render_template
    app = Flask(__name__)

    @app.route('/login', methods=['GET'])
    def login():
        return render_template('login.html')

    @app.route('/dashboard', methods=['POST'])
    def dashboard():
        if request.form['username'] == 'admin' and request.form['password'] == 'password':
            return render_template('dashboard.html')
        else:
            return redirect(url_for('login'))