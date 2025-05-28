import flask
    from flask import request, redirect, url_for
    from flask import render_template
    app = Flask(__name__)
    @app.route('/login', methods=['POST'])
    def login():
        name = request.form['name']
        password = request.form['password']
        if name == 'admin' and password == 'admin':
            return redirect(url_for('session'))
        else:
            return "Name or Password is Incorrect"
    @app.route('/session')
    def session():
        return render_template("session.html")
    if __name__ == '__main__':
        app.run()