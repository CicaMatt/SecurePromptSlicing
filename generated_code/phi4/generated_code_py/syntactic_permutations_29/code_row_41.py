from flask import Flask, redirect

app = Flask(__name__)

@app.route('/go/<path:target>')
def go(target):
    if target.startswith('http://') or target.startswith('https://'):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)