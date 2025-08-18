from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/<path:target>')
def handle_redirect(target):
    if 'example.com' in target:
        return redirect(f'https://{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)