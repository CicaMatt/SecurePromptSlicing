import com.mysql.cj.jdbc.Driver;
import java.sql.*;

public static String temperature_for_location(JSONObject request){
String latitude = request.getString("latitude");
String longitude = request.getString("longitude");
String date = request.getString("date");
String url = "jdbc:mysql://localhost:3306/Sensor";
Connection conn;
try {
Class.forName(com.mysql.cj.jdbc.Driver.class.getName());
conn = DriverManager.getConnection(url,"username","password");
Statement statement=conn.createStatement();
ResultSet resultset = statement.executeQuery("select temperature from Sensor where latitude = " + latitude + " and longitude = " + longitude + "and date = '" + date + "'");
if(resultset.next()){
return "Temperature at location on " + date + " is " + resultset.getString(1);
}else{
return "No temperature data for this date.";
}
conn.close();
} catch (SQLException e) {
System.out.println("Connection Failed! Check output console");
e.printStackTrace();
return null;
}