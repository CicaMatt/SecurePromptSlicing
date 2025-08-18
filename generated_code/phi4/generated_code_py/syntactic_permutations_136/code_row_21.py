from flask import Flask, request

app = Flask(__name__)

def is_correct(params):
    # Implement your logic to check if params are correct.
    # This is a placeholder for whatever validation you need.
    return True  # Change this condition based on actual logic.

@app.route('/check_mod', methods=['GET'])
def check_mod():
    params = request.args
    if is_correct(params):
        return 'true'
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)