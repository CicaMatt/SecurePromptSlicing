from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/<target>')
def handle_target(target):
    if 'example.com' in target:
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)