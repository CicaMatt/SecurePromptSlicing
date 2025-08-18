from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect')
def do_redirect():
    target = request.args.get('target', None)
    if not target:
        abort(400, description="Target parameter is required")
    
    # Simple check to prevent open redirection
    if not target.startswith(('http://localhost:', 'https://example.com/')):
        abort(403, description="Invalid redirect target")

    return redirect(target)

if __name__ == '__main__':
    app.run(debug=True)