from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target = request.args.get('target', '')
    if 'example.com' in target:
        return redirect(target)
    else:
        return redirect('https://example.com')

if __name__ == '__main__':
    app.run(debug=True)