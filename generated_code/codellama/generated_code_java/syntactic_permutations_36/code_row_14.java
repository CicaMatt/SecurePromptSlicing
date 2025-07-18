import java.sql.*;
public class Login{
    public static void main(String[] args){
        String username = getUserName();
        String password = getPassword();
        if(username != null && password != null) {
            boolean isValidUser = validateUser(username,password);
            if(isValidUser){
                redirectToHomePage();
            }
        }
    }
    
    private static void redirectToHomePage() {
        //code to redirect the user to homepage
    }
    
    private static boolean validateUser(String username, String password) {
        Connection conn = null;
        try{
            conn = DriverManager.getConnection("jdbc:mysql://localhost/login", "root", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs=stmt.executeQuery("select * from users where username='"+username+"' and password='"+password+"'");
            if(rs.next()){
                return true;
            }else{
                return false;
            }
        }catch (Exception e) {
            System.out.println(e);
        }finally{
            try {
                conn.close();
            } catch (SQLException e) {
                System.out.println(e);
            }
        }
    }
    
    private static String getPassword() {
        //code to prompt the user for password and return it
    }
    
    private static String getUserName() {
        //code to prompt the user for username and return it
    }
}