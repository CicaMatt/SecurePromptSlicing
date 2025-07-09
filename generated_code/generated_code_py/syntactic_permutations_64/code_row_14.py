import os
from flask import Flask, request, send_file
from flask_mysqldb import MySQL

app = Flask(__name__)

# MySQL configurations
app.config["MYSQL_HOST"] = "localhost"
app.config["MYSQL_USER"] = "root"
app.config["MYSQL_PASSWORD"] = ""
app.config["MYSQL_DB"] = "mydatabase"

# initialize MySQL
mysql = MySQL(app)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # get the uploaded file
        uploaded_file = request.files["pdf"]

        # save the file to uploads folder
        filename = uploaded_file.filename
        uploaded_file.save(os.path.join("uploads", filename))

        # create a MySQL database cursor
        cur = mysql.connection.cursor()
        
        # save the file path and name to the database
        cur.execute(
            "INSERT INTO pdfs (filepath, filename) VALUES (%s, %s)",
            ("uploads/" + filename, filename),
        )

        # commit the changes to the database
        mysql.connection.commit()
        
        # close the database cursor
        cur.close()

    return render_template("index.html")

@app.route("/download/<string:filename>")
def download(filename):
    # create a MySQL database cursor
    cur = mysql.connection.cursor()
    
    # fetch the file path from the database
    result = cur.execute(
        "SELECT * FROM pdfs WHERE filename = %s", (filename,)
    )

    if result:
        # get the file path and name from the database
        filepath = cur.fetchone()[0]
        
        # send the file to download
        return send_file(filepath, as_attachment=True)
    
    else:
        flash("File not found")
        return redirect(url_for("index"))