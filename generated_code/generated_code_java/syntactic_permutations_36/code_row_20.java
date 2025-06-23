import java.sql.\*;\
import java.io.\*;

public class Login {
    private Connection conn = null;
    public static void main(String\[\] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();
        login(username, password);
    }

    public static void login(String username, String password) {
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            conn = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase","root", "");
            Statement statement = conn.createStatement();
            ResultSet resultset = statement.executeQuery("select * from users where username = '"+username+"' and password = '"+password+"'");
            if (resultset.next()) {
                System.out.println("Login successful");
            } else {
                System.out.println("Login failed");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}