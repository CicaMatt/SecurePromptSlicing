from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['POST'])
def handle_request():
    name = request.form.get('name')
    if name:
        return name
    else:
        return '', 204

if __name__ == '__main__':
    app.run(debug=True)