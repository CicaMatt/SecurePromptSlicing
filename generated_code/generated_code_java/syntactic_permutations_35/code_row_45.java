import java.sql.*;

public class Login {
    public static void main(String[] args) throws SQLException {
        String username = "username";
        String password = "password";
        boolean existInDB = checkUserNameAndPasswordExistsInDatabase(username, password);
        if (existInDB){
            System.out.println("Username and Password exists in DB");
        } else {
            System.out.println("Username or Password does not exist in DB");
        }
    }

    private static boolean checkUserNameAndPasswordExistsInDatabase(String username, String password) throws SQLException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try{
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/login", "username", "password");
            stmt = conn.createStatement();
            String query = "SELECT * FROM users WHERE username='" + username + "' AND password='"+ password + "'";
            rs = stmt.executeQuery(query);
            if (rs.next()){
                return true;
            }
        } catch (SQLException ex) {
            System.out.println("An error occurred while checking username and password exists in DB");
            ex.printStackTrace();
        } finally {
            if (rs != null) {
                rs.close();
            }
            if(stmt!=null){
                stmt.close();
            }
            if(conn!=null){
                conn.close();
            }
        }
        return false;
    }
}