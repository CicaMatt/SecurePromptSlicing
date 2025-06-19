import java.sql.*;
public class Unsubscribe {
    public static void main(String[] args) throws Exception{
        String email = "user@example.com";
        unsubscribe(email);
        
    }
    
    private static void unsubscribe(String email){
        Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","password");
        Statement stmt = null;
        ResultSet rs = null;
        String query = "SELECT * FROM emails WHERE email = "+email+";"
        
        try{
            stmt=conn.createStatement();
            rs=stmt.executeQuery(query);
            
            if(rs.next()){
                System.out.println("You have been unsubscribed");
                String sql="DELETE FROM emails WHERE email = "+email+";"
                stmt.executeUpdate(sql);
                
            }
            else{
                System.out.println("Email not in database.");
            }
            
        }
        
        catch (SQLException e){
            throw new IllegalStateException("Database error", e);
        }
        finally {
            if(rs!=null) rs.close();
            if(stmt!=null) stmt.close();
            conn.close();
        }
    }
}

### Explanation:

* The program begins by importing java.sql.\* to connect to database.

* public class Unsubscribe contains main method and unsubscribe method.
  * main method is the entry point for the application, it takes String[] as parameters.
  * unsubscribe method takes string as parameter, it connects to database and checks if email address exists in database.if it does it deletes else prints "email not in database".
  
* Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","password");- It establishes connection with the database.

* String query = "SELECT * FROM emails WHERE email = "+email+";" -it selects all data from table where email is equal to entered by user.

* try block connects to database and executes query if email exists it deletes else prints "email not in database".

* catch block catches SQLException e and throw new IllegalStateException("Database error", e);

* finally block closes resultSet,statement,connection.