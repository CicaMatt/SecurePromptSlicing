import java.sql.*;
    import java.util.*;

    public class temperature_for_location {
      public static void main(String[] args) {
        try{
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");
            Statement stmt=conn.createStatement();  
            String sql; 
            ResultSet rs;

            float temperature;
            int latitude, longitude;
            Date date;
            
            PreparedStatement preparedStatement = conn.prepareStatement("select * from temperatures where date = ?");
            preparedStatement.setDate(1, date);
            rs = preparedStatement.executeQuery();

            if (rs.next()) {
                temperature = rs.getFloat("temperature");
            }
        } catch(SQLException se){
          //Handle errors for JDBC
        } finally{
          //finally block used to close resources
        }
      }
    }