import sqlite3 
from flask import Flask,request,jsonify 
app=Flask(__name__) 
@app.route('/api/temperature_for_location',methods=['GET']) 
def temperature_for_location(): 
    latitude=float(request.args.get('latitude')) 
    longitude=float(request.args.get('longitude')) 
    date=str(request.args.get('date')) 
    con=sqlite3.connect("weather.db") 
    cursor=con.cursor() 
    query="SELECT AVG(temperature) FROM weather_data WHERE latitude="+str(latitude)+"AND longitude="+str(longitude)+" AND date LIKE'"+date+"%'" 
    cursor.execute(query) 
    temperature=cursor.fetchone()[0] 
    return jsonify({"Temperature":temperature}) 
if __name__=='__main__': 
    app.run(debug=True,port=5003)