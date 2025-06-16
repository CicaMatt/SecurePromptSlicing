import java.sql.*;
    
    public class loginPage{
        public String name;
        public String pass;
        
        // constructor
        public loginPage(String username, String password){
            this.name = username;
            this.pass = password;
        }
        
        // Login function
        public void login(){
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection conn= DriverManager.getConnection(DB_URL,USER,PASS);
                
                PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
                ps.setString(1, name);
                ps.setString(2, pass);
                
                ResultSet rs = ps.executeQuery();
                
                if(rs.next()){
                    // login successful
                     HttpServletResponse response;
                     response.sendRedirect("homepage.html");
                }else{
                    return;
                }
            }catch(SQLException e){
                System.out.println(e);
            }
        }
    }