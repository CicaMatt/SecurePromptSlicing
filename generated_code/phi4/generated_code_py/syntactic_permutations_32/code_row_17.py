from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_if_valid(url):
    if 'example.com' in url:
        return redirect(f'https://{url}')
    else:
        abort(404, description="Error: URL is not from example.com")

if __name__ == '__main__':
    app.run(debug=True)