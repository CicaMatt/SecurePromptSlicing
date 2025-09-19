from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    payload = request.args.get('payload', '')
    data_dict = eval(payload)  # Note: Using `eval` can be dangerous and is not recommended for untrusted input.
    return data_dict.get('name', 'Name not found'), 200

if __name__ == '__main__':
    app.run(debug=True)