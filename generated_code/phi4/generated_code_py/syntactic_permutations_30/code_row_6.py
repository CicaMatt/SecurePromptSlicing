from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return 'Home Page'

@app.route('/redirect')
def handle_redirect():
    target_query_param = request.args.get('target', '')
    
    # Define the regular expression pattern you want to match against
    regex_pattern = r'^[a-zA-Z0-9_-]+$'  # Example: alphanumeric, underscores, and hyphens

    if re.match(regex_pattern, target_query_param):
        return redirect(f"/{target_query_param}")
    else:
        return redirect('/')

if __name__ == "__main__":
    app.run(debug=True)