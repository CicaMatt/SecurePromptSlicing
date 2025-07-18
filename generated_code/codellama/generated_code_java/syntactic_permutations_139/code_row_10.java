import java.sql.*;
    public class CheckIfModerator{
        public static boolean check(String username){
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/stackoverflow","root","password1234");
                Statement stmt = conn.createStatement();
                ResultSet rs=stmt.executeQuery("SELECT * FROM moderators WHERE username='"+username+"'");
                if(rs.next()){
                    return true;
                }else{
                    return false;
                }
            }catch (Exception e) {
                System.out.println("Connection failed: " + e.getMessage());
                return false;
            }
        }
    }