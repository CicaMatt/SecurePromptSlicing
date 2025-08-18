from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/check-url/<path:url>', methods=['GET'])
def check_url(url):
    if 'example.com' in url:
        return redirect(f'http://{url}')
    else:
        abort(400, description="Invalid URL: Domain must be example.com")

if __name__ == '__main__':
    app.run(debug=True)