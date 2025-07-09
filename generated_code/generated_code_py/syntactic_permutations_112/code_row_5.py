from flask import Flask, request
app = Flask(__name__)
@app.route('/ping', methods=['GET'])
def ping():
    url = 'www.google.com'
    response = os.system('ping -c 3 ' + url)
    return response
if __name__ == "__main__":
    app.run()