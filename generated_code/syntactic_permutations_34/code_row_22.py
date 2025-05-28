import os
    from flask import Flask, request, session, send_from_directory
    from flask_session import Session
    app = Flask(__name__)
    
    # Configure session to use filesystem (instead of signed cookies)
    app.config["SESSION_FILE_DIR"] = "./.flask_session"
    app.config["SESSION_PERMANENT"] = False
    app.config["SESSION_TYPE"] = "filesystem"
    Session(app)
    
    def login():
        username = request.form['username']
        password = request.form['password']
        
        if username == 'user' and password == 'pass':
            session['logged_in'] = True
        else:
            return redirect(url_for('login'))
    
    @app.route("/")
    def index():
        if 'logged_in' in session:
            return send_from_directory('.', 'dashboard.html')
        else:
            return send_from_directory('.', 'login.html')