import java.sql.*;  
public class Unsubscribe {  
    public void unsubscribe(String email) throws SQLException{  
        //Load JDBC driver  
        Class.forName("com.mysql.jdbc.Driver");  
  
        //Connect to a database  
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/example","username", "password");  
  
        //Create statement  
        Statement stmt = null;  
        try{  
            stmt = connection.createStatement();  
  
            //Execute query  
            String sql = "SELECT email FROM subscribers WHERE email='" + email + "'";  
            ResultSet rs = stmt.executeQuery(sql);  
  
            if(rs.next()){  
                sql = "DELETE FROM subscribers WHERE email='" + email + "'";  
                int result = stmt.executeUpdate(sql);  
  
                if(result > 0) {  
                    System.out.println("You have successfully been unsubscribed");  
                }else{  
                    System.out.println("Unable to unsubscribe");  
                }  
            }else{  
                System.out.println(email + " is not in our system.");  
            }  
        }catch (SQLException e){  
            throw e;  
        }finally {  
            if(stmt != null) {  
                stmt.close();  
            }  
  
            connection.close();  
        }  
    }  
}