from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def api():
    params = request.args.to_dict()
    return params.get('name', '')

if __name__ == '__main__':
    app.run(debug=True)