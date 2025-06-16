import java.sql.*;

    public class Login {
        public static void main(String args[]){
            String username = "user";
            String password = "pass";
            String url = "jdbc:mysql://localhost/login_page";
            Connection con = null;
            PreparedStatement pst=null;
            ResultSet rs=null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                con = DriverManager.getConnection(url,"root","password");
                String query="select * from users where username = ? and password = ?";
                pst=con.prepareStatement(query);
                pst.setString(1,username);
                pst.setString(2,password);
                rs=pst.executeQuery();
                if(rs.next()){
                    response.sendRedirect("success");
                }else{
                    response.sendRedirect("cant_login");
                }
            } catch (Exception e) {
                response.sendRedirect("internal_server_error");
            }finally{
                rs.close();
                pst.close();
                con.close();
            }
        }
    }