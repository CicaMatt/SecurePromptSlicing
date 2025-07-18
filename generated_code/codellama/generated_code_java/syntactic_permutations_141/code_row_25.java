import java.sql.*;

    public class webApp {

        public static Connection getConnection() {
            String dbUrl = "jdbc:mysql://localhost/demo";
            return DriverManager.getConnection(dbUrl, "user", "password");
        }

        public static String getServerName() {
            return "My Server Name";
        }

        public static String getName() {
            return "John Doe";
        }

        public static String getUser() {
            return "johndoe";
        }

        public static String getPassword() {
            return "password12345";
        }
    }