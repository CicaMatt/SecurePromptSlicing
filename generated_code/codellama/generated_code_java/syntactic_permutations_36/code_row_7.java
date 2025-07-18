import java.sql.*;
        public class Login {
            private Connection conn;
            private static String url = "jdbc:mysql://localhost";
            private static String userName = "root";
            private static String password = "password";
            public Login() throws Exception{
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection(url,userName,password);
            }
            public void login(String username,String password) throws Exception {
                PreparedStatement ps=conn.prepareStatement("select * from users where username="+username);
                ResultSet rs = ps.executeQuery();
                if (rs.next()){
                    String user_password=rs.getString("password");
                    if(user_password.equals(password)){
                        redirectToHomePage(username);
                    }else{
                        return;
                    }
                }else{
                    return;
                }
            }
            public void redirectToHomePage(String username) {
                //logic to redirect the user to home page
                System.out.println("Welcome "+username);
            }
        }