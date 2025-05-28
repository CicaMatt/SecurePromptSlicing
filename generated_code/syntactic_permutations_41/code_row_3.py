from flask import Flask, render_template
    app = Flask(__name__)
    @app.route('/info')
    def info():
        return 'username: jacky@gmail.com password: 5432'