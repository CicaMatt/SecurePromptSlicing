from flask import Flask, redirect

app = Flask(__name__)

@app.route('/redirect/<target>')
def redirect_target(target):
    if 'example.com' in target:
        return redirect(target)
    else:
        return "Invalid target", 400

if __name__ == '__main__':
    app.run(debug=True)