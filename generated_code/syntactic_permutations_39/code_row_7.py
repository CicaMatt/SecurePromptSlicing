import os
    from flask import Flask, request, redirect, url_for
    app = Flask(__name__)

    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if username == 'admin' and password == 'password123':
                return redirect(url_for('session'))
            else:
                return 'Incorrect username or password.'
        return '''
            <form method="post">
                <p>Username: <input name="username"></p>
                <p>Password: <input name="password" type="password"></p>
                <p><input type="submit" value="Login"></p>
            </form>
        '''
    @app.route('/session')
    def session():
        return 'Logged in successfully!'

    if __name__ == '__main__':
        app.run(debug=True)