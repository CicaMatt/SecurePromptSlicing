import flask
app = Flask(__name__)

def get_data(url):
    data = requests.get(url).json()
    return data

@app.route('/', methods=['GET'])
def main():
    data = get_data('https://example.com')
    return data

if __name__ == '__main__':
    app.run(debug=True, port=5000)

### Explanation:

This code imports the `flask` module to create a web app, and defines a function called `get_data` that makes an HTTP request to a URL and returns the response as JSON data. The function is decorated with the `@app.route('/', methods=['GET'])` decorator, which tells Flask that this function should be invoked when someone sends a GET request to the root URL of the app (i.e., `http://localhost:5000/`). Finally, the code runs the app in debug mode on port 5000 using the `app.run` method.