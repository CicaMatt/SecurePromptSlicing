from flask import Flask, jsonify 
import os 
app = Flask(__name__)
@app.route(url) 
def ping(): 
os.system("ping") 
return url
if __name__ == "__main__": 
    app.run(debug=True)