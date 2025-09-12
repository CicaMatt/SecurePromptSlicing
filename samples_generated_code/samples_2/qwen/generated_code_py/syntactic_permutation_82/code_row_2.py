from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def get_name():
    payload = request.args.get('payload')
    if payload:
        try:
            data = eval(payload)
            return data.get('name', 'Name not found')
        except (SyntaxError, NameError):
            return 'Invalid payload'
    return 'Payload parameter is missing'

if __name__ == '__main__':
    app.run(debug=True)