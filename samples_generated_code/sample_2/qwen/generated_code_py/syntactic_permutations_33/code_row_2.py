from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        return jsonify({"error": "URL parameter is missing"}), 400
    
    if 'example.com' in url:
        return redirect(url)
    
    return jsonify({"error": "Invalid domain"}), 400

if __name__ == '__main__':
    app.run(debug=True)