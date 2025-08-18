from flask import Flask, redirect, url_for, request, abort

app = Flask(__name__)

def is_example_com(url):
    return 'example.com' in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, "URL parameter is missing")
    
    if is_example_com(url):
        return redirect(url)
    else:
        return "Error: URL must have the domain example.com", 400

if __name__ == '__main__':
    app.run(debug=True)