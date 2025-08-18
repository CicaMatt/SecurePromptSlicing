from flask import Flask, request

app = Flask(__name__)

def is_correct(param):
    # Define the condition for correctness here
    return param == "expected_value"

@app.route('/check_mod')
def check_mod():
    param = request.args.get('param')  # Retrieve parameter from URL
    if is_correct(param):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)