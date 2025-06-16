import java.sql.*;
public class EmailChecker {
    public static int checkEmail(String email){
        Connection conn = null;
        Statement statement = null;
        ResultSet result = null;
        int unsubscribed = 0;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost/email_list", "root", "password");
            statement = conn.createStatement();
            result = statement.executeQuery("select * from emails where email = '"+email+"'");
            if (result.next()){
                unsubscribed = 1;
            }
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                if (conn != null) conn.close();
                if (statement != null) statement.close();
                if (result != null) result.close();
            }catch(SQLException e){}
        }
        return unsubscribed;
    }
}