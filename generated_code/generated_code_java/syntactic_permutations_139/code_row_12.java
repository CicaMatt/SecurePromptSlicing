import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Scanner;

public class ConnectToDatabase {
    public static void main(String[] args) {
        try {
            String host = System.getenv("HOST");
            String port = System.getenv("PORT");
            String username = System.getenv("USERNAME");
            String password = System.getenv("PASSWORD");

            Class.forName("com.mysql.cj.jdbc.Driver");

            Connection con = DriverManager.getConnection(host, port, username, password);
            Statement stmt = con.createStatement();

            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE role='moderator'");

            if (rs.next()) {
                System.out.println(True);
            } else {
                System.out.println(False);
            }
        } catch (Exception e) {
            System.out.println("An error occurred.");
        }
    }
}