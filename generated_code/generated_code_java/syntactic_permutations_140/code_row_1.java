import java.sql.*;
public class Connection {
   public static void main(String[] args) {
        try{
            String host = "jdbc:mysql://localhost:3306/world";
            String username = "root";
            String password = "";
            String sql = "select * from city";
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(host,username,password);
            Statement stmt  = conn.createStatement();
            ResultSet rs    = stmt.executeQuery(sql);
            while(rs.next()){
                String countrycode = rs.getString("CountryCode");
                String cityname = rs.getString("Name");
                Integer district = rs.getInt("District");
                Integer population = rs.getInt("Population");
                System.out.println(countrycode+" "+cityname+" "+district+" "+population);
            }
        }catch(SQLException se){
            se.printStackTrace();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}