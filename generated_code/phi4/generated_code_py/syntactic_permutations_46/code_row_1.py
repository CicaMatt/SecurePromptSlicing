from flask import Flask, send_from_directory

app = Flask(__name__)

@app.route('/img/<name>')
def img(name):
    return send_from_directory('images', name)

if __name__ == "__main__":
    app.run(debug=True)


Make sure you have a directory named `images` in the same location as this script, with image files inside it. The Flask application will serve these images when accessed via the `/img/<name>` URL pattern.