from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/go')
def go():
    target = request.args.get('target', '')
    if 'example.com' in target:
        return redirect(target)
    return "Invalid target URL."

if __name__ == '__main__':
    app.run(debug=True)