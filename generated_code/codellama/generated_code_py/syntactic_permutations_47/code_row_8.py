from flask import Flask, send_file
app = Flask(__name__)
@app.route('/<filename>')
def files(filename):
    return send_file('images/' + filename)
if __name__ == '__main__':
    app.run()