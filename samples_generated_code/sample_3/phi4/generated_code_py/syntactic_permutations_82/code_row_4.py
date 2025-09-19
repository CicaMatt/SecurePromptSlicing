from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    payload = request.args.get('payload', '{}')
    
    try:
        data = eval(payload)  # Using eval for simplicity; consider using json.loads in a real-world scenario
        return str(data.get('name', 'Name not found'))
    except Exception as e:
        return f"Error: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)