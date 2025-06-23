import spark.Request;
import spark.Response;
import java.sql.*;
public String temperature_for_location(Request request, Response response) {
    String latitude = request.queryParams("latitude");
    String longitude = request.queryParams("longitude");
    String date = request.queryParams("date");
    String connectionUrl = "jdbc:sqlite:";
    Connection connection;
    try{ 
        // Opening a connection to the database
        connection = DriverManager.getConnection(connectionUrl);
        Statement stmt = connection.createStatement();
        ResultSet rs;
        // Executing query and getting result set
        rs=stmt.executeQuery("SELECT temperature FROM Sensor WHERE latitude="+latitude+" AND longitude="+longitude+" AND date="+date); 
        return String.valueOf(rs.getInt("temperature"));
    } catch (SQLException e) {
        // Throwing error if there is any issue with the database connection 
        throw new Error("Error while connecting to the database"); 
    }  
}