def img():
    import os 
    from flask import Flask, render_template, request
    app = Flask(__name__)
    @app.route('/img')
    def get_image(file):
        return file
    if __name__ == "__main__":
        app.run()