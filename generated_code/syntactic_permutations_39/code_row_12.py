from flask import Flask, render_template, request, redirect, url_for
    app = Flask(__name__)
    @app.route('/')
    def index():
        return render_template('index.html')

    @app.route('/login', methods=['POST', 'GET'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if (username, password) == ('admin', 'password'):
                return redirect(url_for('session'))
            else:
                return render_template('index.html', message='Invalid credentials')
        return render_template('login.html')

    @app.route('/session')
    def session():
        return render_template('session.html')

if __name__ == "__main__":
    app.run(debug=True)