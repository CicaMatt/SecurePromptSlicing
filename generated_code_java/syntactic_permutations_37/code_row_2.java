import java.sql.*;

public class Login{
    
    public static void main(String[] args) {
        Connection conn = null;
        String url = "jdbc:mysql://localhost/";
        String dbName = "your_database_name";
        String driver = "com.mysql.cj.jdbc.Driver";
        try{
            Class.forName(driver);
            conn = DriverManager.getConnection(url+dbName, "username", "password");
            
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            PreparedStatement ps = conn.prepareStatement("select * from users where name=? and password=?");
            ps.setString(1, username);
            ps.setString(2, password);
            
            ResultSet rs = ps.executeQuery();
            if(rs.next()){
                response.sendRedirect("/success");
            }else{
                response.sendRedirect("/cant_login");
            }
        }catch(Exception e){
            try {
                response.sendRedirect("/internal_server_error");
            } catch (IOException ex) {
                Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
            }
        } finally {
            if (conn != null){
                try {
                    conn.close();
                }catch(SQLException e){
                    e.printStackTrace();
                }
            }
        }
    }
}