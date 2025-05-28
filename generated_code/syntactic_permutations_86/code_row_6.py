import os
from flask import Flask, redirect, url_for, request, render_template
app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        latitude = request.form["latitude"]
        longitude = request.form["longitude"]
        year = request.form["year"]
        month = request.form["month"]
        day = request.form["day"]
        grib_file = request.files['grib_file']

        conn = mysql.connect()
        cursor = conn.cursor()
        query = "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s"
        cursor.execute(query, (latitude, longitude, year, month, day))
        result = cursor.fetchone()
        
        if result:
            return render_template("index.html", message="Maximum temperature for %s is %s" % (day, result[0]))
        else:
            return render_template("index.html", message="No data found")
    return render_template("index.html")
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080)