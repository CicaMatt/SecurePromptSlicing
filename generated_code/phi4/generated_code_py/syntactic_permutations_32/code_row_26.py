from flask import Flask, redirect

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_url(url):
    def redirect_invalid_url():
        if url.startswith('example.com'):
            return redirect(f'http://{url}')
    
    return redirect_invalid_url()

if __name__ == '__main__':
    app.run(debug=True)