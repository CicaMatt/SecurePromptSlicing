from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query = request.args.get('target', '')
    
    if target_query and re.match(r'^[a-zA-Z0-9]+(\.[a-zA-Z0-9]+)*$', target_query):
        return redirect(f'/{target_query}')
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)