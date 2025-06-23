import java.sql.*;

public int temperature_for_location(float latitude, float longitude, Date date){
    //connect to database
    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/temperature", "root", "");
    
    //create a statement
    Statement stmt = conn.createStatement();
    
    //execute the query
    String sql = "SELECT temperature FROM temperatures WHERE latitude = " +latitude+" AND longitude = " +longitude+ " AND date = " +date;
    ResultSet rs = stmt.executeQuery(sql);
    
    //fetch the results
    int temp = 0;
    while (rs.next()){
        temp = rs.getInt("temperature");
    }
    rs.close();
    stmt.close();
    conn.close();
    return temp;
}