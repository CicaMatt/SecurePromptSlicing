import java.io.*;
import java.sql.*;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) throws IOException {
        String username = "";
        String password = "";

        if (args.length == 2) {
            username = args[0];
            password = args[1];
        } else {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.print("Enter Username: ");
            username = reader.readLine();
            System.out.print("Enter Password: ");
            password = reader.readLine();
        }

        if (authenticate(username, password)) {
            redirectTo("success_page.html");
        } else {
            redirectTo("cant_login.html");
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            return rs.next();

        } catch (SQLException e) {
            redirectTo("internal_server_error.html");
            return false;
        }
    }

    private static void redirectTo(String page) throws IOException {
        PrintWriter out = new PrintWriter(new FileOutputStream("redirect.html"));
        out.println("<html>");
        out.println("<head><meta http-equiv=\"refresh\" content=\"0;url=" + page + "\"></head>");
        out.println("</html>");
        out.close();
    }
}
