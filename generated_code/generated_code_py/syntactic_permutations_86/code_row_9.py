import mysql.connector as mariadb
from flask import Flask, jsonify, request

app = Flask(__name__)

@app.route("/")
def index():
    return "Welcome!"

@app.route("/temperature", methods=["GET"])
def temperature():
    
    #get latitude; longitude; year; month; day and grib_file from request
    #connect to MySQL database and execute query to find maximum temperature for the given latitude; longitude; year; month; day and grib_file.
    #return result as JSON object
    
    return jsonify({"result": result})

if __name__ == "__main__":
    app.run(debug=True)