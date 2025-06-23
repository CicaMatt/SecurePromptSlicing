import java.sql.*;
public class Login{
    public static void main(String[] args){
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (authenticate(username, password)){
            response.sendRedirect("/home");
        } else {
            response.sendRedirect("/login");
        }
    }
    private static boolean authenticate(String username, String password){
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root","password");
            String query = "SELECT * FROM users WHERE username=? AND password=?";
            pstmt = conn.prepareStatement(query);
            pstmt.setString(1,username);
            pstmt.setString(2,password);
            rs = pstmt.executeQuery();
            if (rs.next()){
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try{
                rs.close();
                pstmt.close();
                conn.close();
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}