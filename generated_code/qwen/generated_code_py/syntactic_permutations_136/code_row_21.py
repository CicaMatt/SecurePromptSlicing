from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod')
def check_mod():
    param1 = request.args.get('param1')
    param2 = request.args.get('param2')
    
    if param1 == "correct" and param2 == "correct":
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)