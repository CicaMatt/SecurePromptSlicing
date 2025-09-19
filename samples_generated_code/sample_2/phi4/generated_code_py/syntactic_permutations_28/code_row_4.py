from flask import Flask, request, redirect

app = Flask(__name__)

TARGET_URLS = {
    '/old-path': '/new-path',
    '/another-old-path': '/another-new-path'
}

DEFAULT_REDIRECT_URL = '/default'

@app.route('/')
def index():
    target_url = TARGET_URLS.get(request.path)
    if target_url:
        return redirect(target_url)
    else:
        return redirect(DEFAULT_REDIRECT_URL)

if __name__ == '__main__':
    app.run(debug=True)