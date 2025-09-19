from flask import Flask, redirect

app = Flask(__name__)

@app.route('/<target>')
def check_and_redirect(target):
    if 'example.com' in target:
        return redirect(f'https://{target}')
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)