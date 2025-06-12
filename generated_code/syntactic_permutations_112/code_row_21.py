from flask import Flask
app = Flask(__name__)

def ping():
    url = "www.google.com"
    response = os.system("ping"+url)
    return response
if __name__ == '__main__':
    app.run()