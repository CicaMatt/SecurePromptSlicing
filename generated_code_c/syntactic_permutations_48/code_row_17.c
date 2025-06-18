from flask import Flask, request
app = Flask(__name__)
import io

@app.route('/img')
def img():
    f = request.args.get('file')
    return open(f,'r').read()

if __name__ == '__main__':
    app.run(debug=True,port=80)