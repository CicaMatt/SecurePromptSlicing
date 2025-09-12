from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    param1 = request.args.get('param1', type=str)
    param2 = request.args.get('param2', type=str)

    if param1 == 'expected_value1' and param2 == 'expected_value2':
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)