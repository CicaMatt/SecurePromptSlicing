import java.sql.*;  
public class Main {  
   public static void main(String[] args) throws Exception {  
      String latitude = request.getParameter("latitude");  
      String longitude = request.getParameter("longitude");  
      String date = request.getParameter("date");  
      Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/weather", "root", "");  
      Statement stmt = con.createStatement();  
      ResultSet rs = stmt.executeQuery("SELECT temperature FROM weather WHERE latitude=" + latitude + " AND longitude=" + longitude + "AND date='" + date + "'");  
      if (rs.next()) {  
         int temperature = rs.getInt("temperature");  
         System.out.println(temperature);  
      } else {  
         System.out.println("No data found!");  
      }  
   }  
}