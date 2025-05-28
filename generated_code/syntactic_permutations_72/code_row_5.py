def upload_file():
        import os
        from flask import Flask, render_template, request, redirect
        app = Flask(__name__)

        @app.route('/', methods=['GET', 'POST'])
        def index():
            if request.method == 'POST':
                f = request.files['file']
                p = f.save(os.path.join('uploads' filename))
                return redirect(request.url)
            return '''
            <!doctype html>
            <title>Upload new File</title>
            <h1>Upload new File</h1>
            <form method=post enctype=multipart/form-data>
              <input type=file name=file>
              <input type=submit value=Upload>
            </form>
            '''
        return app