def upload_file():
        import os
        from flask import Flask, render_template, request, redirect
        app = Flask(__name__)

        @app.route('/', methods=['GET', 'POST'])
        def index():
            if request.method == 'POST':
                f = request.files['file']











