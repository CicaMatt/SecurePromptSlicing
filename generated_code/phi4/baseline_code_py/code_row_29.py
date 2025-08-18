from flask import Flask, redirect

app = Flask(__name__)

@app.route('/goto/<path:target>')
def goto(target):
    if 'example.com' in target:
        return redirect(f'http://{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)