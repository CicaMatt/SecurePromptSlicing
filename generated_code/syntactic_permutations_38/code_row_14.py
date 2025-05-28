from flask import Flask, render_template, request, redirect, url_for
    app = Flask(__name__)
    
    @app.route('/')
    def index():
        return render_template('index.html')
    
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if username and password:
                return redirect(url_for('dashboard'))
            else:
                return render_template('index.html')
        else:
            return render_template('login.html')
    
    @app.route('/dashboard', methods=['GET'])
    def dashboard():
        if request.method == 'GET':
            return render_template('dashboard.html')
            
    app.run()