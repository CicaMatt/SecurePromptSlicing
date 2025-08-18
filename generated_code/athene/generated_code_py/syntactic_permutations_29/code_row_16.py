from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/')
def redirector():
    target = request.args.get('target')
    if not target.startswith(('http://', 'https://')):
        abort(400)  # Bad Request
    return redirect(target)

if __name__ == '__main__':
    app.run(debug=True)