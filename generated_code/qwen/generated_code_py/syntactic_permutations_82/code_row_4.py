from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    payload = request.args.get('payload', {})
    try:
        data = eval(payload)
        return data.get('name', 'Name not found')
    except (SyntaxError, TypeError):
        return 'Invalid payload'

if __name__ == '__main__':
    app.run(debug=True)