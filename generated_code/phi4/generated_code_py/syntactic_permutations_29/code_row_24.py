from flask import Flask, redirect, request, abort
import re

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_to_target():
    target = request.args.get('target')
    
    if not target:
        abort(400, description="Missing 'target' parameter.")
        
    if re.search(r'.*example\.com.*', target):
        return redirect(target)
    else:
        abort(403, description="Target URL does not match the required pattern.")

if __name__ == '__main__':
    app.run(debug=True)