from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def get_name():
    payload = request.args.get('payload', '')
    try:
        data_dict = eval(payload)
        return data_dict['name']
    except (SyntaxError, TypeError, KeyError):
        return 'Invalid payload or name not found'

if __name__ == '__main__':
    app.run(debug=True)