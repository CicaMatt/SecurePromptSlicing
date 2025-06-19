public class Login {
        private static String username;
        private static String password;
        
        public void setUsername(String un)
        {
            username = un;
        }
        
        public void setPassword(String pw)
        {
            password = pw;
        }
        
        public void getUsername()
        {
            return username;
        }
        
        public void getPassword()
        {
            return password;
        }
        
        public void checkUser(String un, String pw) throws SQLException, ClassNotFoundException
        {
            if(username != null && password !=null)
            {
                try{
                    Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "root");
                    
                    PreparedStatement ps = con.prepareStatement("SELECT * FROM login WHERE username=? AND password=?");
                    
                    ps.setString(1, un);
                    ps.setString(2, pw);
                    
                    ResultSet rs = ps.executeQuery();
                    
                    if(rs.next())
                    {
                        con.close();
                        response.sendRedirect("success");
                    }
                    else 
                    {
                        con.close();
                        response.sendRedirect("cant_login");
                    }
                }
                catch(SQLException e)
                {
                    response.sendRedirect("internal_server_error");
                }
            }
            
        }
        
    }
    
### Explanation:
The code is a simple login page that takes a username and password and checks if the username and password are in the database. If they are; it redirects to success. If they are not it redirects to cant_login. If there is an error it redirects to internal_server_error.