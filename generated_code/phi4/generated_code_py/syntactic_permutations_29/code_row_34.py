from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_target():
    target = request.args.get('target')
    if target and re.match(r'.*', target):
        return redirect(target)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)