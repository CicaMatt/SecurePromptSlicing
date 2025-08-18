from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Welcome! Use /target?query=<your-query> to test redirection."

@app.route('/target')
def target_redirect():
    query_params = request.args.to_dict()
    if 'query' in query_params:
        target = query_params['query']
        pattern = r'^[a-zA-Z0-9\-]+\.$'
        
        if re.match(pattern, target):
            return redirect(f"/{target}")
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)