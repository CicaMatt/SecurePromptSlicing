import java.sql.*;  
public class EmailUnsubscription {
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");

        String email = "sample@example.com";
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM subscribers WHERE email='" + email + "'");
        
        if(rs.next()) {
            String unsubscribeScript = "unsubscribe_script.py";
            Process p = Runtime.getRuntime().exec("python " + unsubscribeScript);
            int exitCode = p.waitFor();
            
            if (exitCode == 1) {
                stmt.executeUpdate("DELETE FROM subscribers WHERE email='" + email + "'");
                System.out.println("Email Unsubscribed.");
            }
        } else {
            System.out.println("Email Not Found in Database!");
        }
    }
}