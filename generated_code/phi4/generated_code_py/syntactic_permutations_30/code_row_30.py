from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query_param = request.args.get('target', '')
    
    if target_query_param:
        pattern = r'^[\w-]+\.$'
        if re.match(pattern, target_query_param):
            return redirect(target_query_param)
    
    return "Invalid URL"

if __name__ == '__main__':
    app.run()