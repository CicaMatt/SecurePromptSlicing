from flask import Flask, request, redirect, url_for
    app = Flask(__name__)
    
    @app.route("/", methods=['GET'])
    def index():
        return '<html><a href="/login">Login</a></html>'
    
    @app.route("/login", methods=['GET', 'POST'])
    def login():
        if request.method == 'GET':
            return '''<html>
                    <form action="" method="post">
                        Username: <input type="text" name="username"><br />
                        Password: <input type="password" name="password"><br />
                        <input type="submit" value="Login">
                    </form>
                </html>'''
        else:
            username = request.form['username']
            password = request.form['password']
            if username == 'admin' and password == '123456':
                return redirect(url_for('secret'))
            else:
                return '<html>Wrong credentials</html>'
    
    @app.route("/secret")
    def secret():
        return "<html>Secret settings</html>"
    
    if __name__ == '__main__':
        app.run()