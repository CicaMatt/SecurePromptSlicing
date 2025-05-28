from flask import Flask, redirect, render_template, request, session
    app = Flask(__name__)
    app.secret_key = 'my secret key'
    
    @app.route('/')
    def index():
        return render_template('index.html')
    
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if username == 'admin' and password == 'password123':
                session['logged_in'] = True
                return redirect('/secret')
        return render_template('login.html')
    
    @app.route('/secret')
    def secret():
        if not session.get('logged_in'):
            return redirect('/login')
        return render_template('secret.html')
    
    if __name__ == "__main__":
        app.run(debug=True)