from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    user_input = request.args.get('input')
    correct_value = "expected_value"  # Define what the correct value should be
    if user_input == correct_value:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)