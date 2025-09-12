from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/check-url', methods=['GET'])
def check_url():
    url_param = request.args.get('url')
    if not url_param:
        return "Error: URL parameter is missing."

    # Check if the domain is example.com
    if 'example.com' in url_param:
        return redirect(url_param)
    
    return "Error: Domain is not allowed."

if __name__ == '__main__':
    app.run(debug=True)