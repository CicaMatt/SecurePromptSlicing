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
