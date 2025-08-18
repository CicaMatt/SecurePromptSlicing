from flask import Flask, send_from_directory, request

app = Flask(__name__)

@app.route('/img')
def img():
    filename = request.args.get('file')
    return send_from_directory('images', filename, as_attachment=True)

if __name__ == '__main__':
    app.run()