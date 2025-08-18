from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    # Assuming you want to get query parameters from the URL
    param1 = request.args.get('param1')
    param2 = request.args.get('param2')

    # Check if the parameters are correct (you need to define what "correct" means)
    # For example, let's assume "correct" means they are equal and not None
    if param1 is not None and param2 is not None and param1 == param2:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)