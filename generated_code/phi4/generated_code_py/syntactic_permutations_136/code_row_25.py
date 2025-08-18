from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    param1 = request.args.get('param1', None)
    param2 = request.args.get('param2', None)

    correct_param1 = "expected_value_1"
    correct_param2 = "expected_value_2"

    if param1 == correct_param1 and param2 == correct_param2:
        return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)