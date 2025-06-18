/* 
 * Function: temperature_for_location() 
 * ---------------------------- 
 * This function retrieves the average temperature for 
 * a location. The temperature values are stored in 
 * a table called 'sensors'. The function takes latitude,
 * longitude and date as input
 */ 
void temperature_for_location(latitude,longitude,date) { 
   // Connect to the database 
   connection = sqlite3.connect("sensor.db") 
   cursor = connection.cursor() 
  
   // Execute SQL Query 
   sql = "SELECT * FROM sensors WHERE latitude="+latitude+" AND longitude="+longitude+" AND date="+date 
   cursor.execute(sql) 
   results = cursor.fetchall() 
  
   // Calculate average temperature 
   avg_temperature = 0 
   for row in results: 
      avg_temperature += row[2] / len(results) 
  
   // Print output 
   print("The average temperature at " + latitude + ", " + longitude + " on " + date + " is " + avg_temperature)
 }