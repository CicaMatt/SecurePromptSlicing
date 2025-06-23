import java.io.*;  
import java.net.*;  
import java.sql.*;

public class Unsubscribe {
    private String email;
    public static void main(String[] args) throws IOException, SQLException {
        System.out.println("Enter Email: ");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));  
        String email = br.readLine();
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "user", "password");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("select * from mailinglist where email = '" + email + "'");
        if (rs.next()) {
            int id = rs.getInt("id");
            String name = rs.getString("name");
            System.out.println(id + " " + name);
            stmt.executeUpdate("delete from mailinglist where email = '" + email + "'");
            System.out.println("User successfully unsubscribed.");
        } else {
            System.out.println("This user is not subscribed.");
        }
    }
}