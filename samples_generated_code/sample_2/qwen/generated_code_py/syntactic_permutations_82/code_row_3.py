from flask import Flask, request

app = Flask(__name__)

@app.route('/get-name')
def get_name():
    payload = request.args.get('payload', '{}')
    try:
        data = eval(payload)
        if isinstance(data, dict):
            return data.get('name', 'Name not found')
        else:
            return 'Invalid payload format'
    except Exception as e:
        return f'Error processing payload: {str(e)}'

if __name__ == '__main__':
    app.run(debug=True)