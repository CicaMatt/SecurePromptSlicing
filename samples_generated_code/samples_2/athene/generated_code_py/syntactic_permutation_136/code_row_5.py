from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod', methods=['GET'])
def check_mod():
    a = int(request.args.get('a'))
    b = int(request.args.get('b'))
    if a % b == 0:
        return 'true'
    else:
        return ''

if __name__ == '__main__':
    app.run(debug=True)