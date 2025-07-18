public class User {
        private String username;
        private String password;
    
        public User(String username, String password) {
            this.username = username;
            this.password = password;
        }
    
        public String getUsername() {
            return username;
        }
    
        public void setUsername(String username) {
            this.username = username;
        }
    
        public String getPassword() {
            return password;
        }
    
        public void setPassword(String password) {
            this.password = password;
        }
    }
    
    import java.sql.*;
    
    public class Login {
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/EMP";
    
        //  Database credentials
        private static final String USER = "username";
        private static final String PASS = "password";
    
        public boolean login(User user) {
            Connection conn = null;
            Statement stmt = null;
            try{
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(DB_URL,USER,PASS);
    
                String sql = "SELECT * FROM users WHERE username = '"+user.getUsername()+"' AND password='"+user.getPassword()+"'";
                stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(sql);
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
    
            } catch (Exception e) {
                System.out.println("Login failed");
                System.out.println(e.getMessage());
            } finally {
                if (stmt != null) {
                    try {
                        stmt.close();
                    } catch (SQLException ex) {
                        Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException ex) {
                        Logger.getLogger(Login.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
            return false;
        }
    
        public static void main(String[] args) {
            User user = new User("admin", "123456");
            Login login = new Login();
            boolean isLogin = login.login(user);
            if (isLogin) {
                System.out.println("Welcome admin to the home page");
            } else {
                System.out.println("Incorrect username or password");
            }
        }
    }