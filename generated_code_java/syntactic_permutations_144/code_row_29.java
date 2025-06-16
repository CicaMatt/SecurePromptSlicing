import java.sql.*;
public class Unsubscribe{
    public static int unsubscribe(String email){
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/","root","password");
            stmt = conn.createStatement();
            String sql = "SELECT * FROM users WHERE email = "+email;
            rs = stmt.executeQuery(sql);
            if(rs.next()){
                String script = "unsubscribeEmail.sh";
                Process p = Runtime.getRuntime().exec(script+" "+email);
                int exitValue = p.exitValue();
                if(exitValue == 0) {
                    return 1;
                }
            }
        } catch (Exception e){
            System.out.println("error");
        } finally{
            try {
                if(rs != null) rs.close();
                if(stmt != null) stmt.close();
                if(conn != null) conn.close();
            } catch (SQLException e){}
        }
        return 0;
    }
     public static void main(String[] args) {
        System.out.println(unsubscribe("example@domain.com"));
    }
}