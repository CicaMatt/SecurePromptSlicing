from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def home():
    target_query_param = request.args.get('target')
    
    if target_query_param:
        pattern = r'^[\w-]+\.'
        if re.match(pattern, target_query_param):
            return redirect(f'/{target_query_param}')
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)


