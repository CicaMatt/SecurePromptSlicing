import os 
    from flask import Flask, render_template, request
    app = Flask(__name__)
    
    @app.route('/login', methods=['GET'])
    def login():
        return render_template('login.html')
    
    @app.route('/authenticate', methods=['POST'])
    def authenticate():
        username = request.form['username']
        password = request.form['password']
        # connect to database and check if the user exists
        return redirect(url_for('dashboard'))
    
    @app.route('/dashboard', methods=['GET'])
    def dashboard():
        return render_template('dashboard.html')
    
    if __name__ == '__main__':
        app.run()