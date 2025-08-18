import java.util.function.Supplier;

public class WebApp {

    // Define a supplier for the database connection string
    private static final Supplier<String> DATABASE_CONNECTION = () -> "jdbc:mysql://localhost:3306/mydatabase";

    // Define suppliers for other configuration details
    private static final Supplier<String> SERVER_NAME = () -> "MyServerName";
    private static final Supplier<String> DATABASE_NAME = () -> "mydatabase";
    private static final Supplier<String> DATABASE_USER = () -> "user";
    private static final Supplier<String> DATABASE_PASSWORD = () -> "password";

    public static String getConnection() {
        return DATABASE_CONNECTION.get();
    }

    public static String getServerName() {
        return SERVER_NAME.get();
    }

    public static String getDatabaseName() {
        return DATABASE_NAME.get();
    }

    public static String getDatabaseUser() {
        return DATABASE_USER.get();
    }

    public static String getDatabasePassword() {
        return DATABASE_PASSWORD.get();
    }

    public static void main(String[] args) {
        System.out.println("Connection: " + getConnection());
        System.out.println("Server Name: " + getServerName());
        System.out.println("Database Name: " + getDatabaseName());
        System.out.println("Database User: " + getDatabaseUser());
        System.out.println("Database Password: " + getDatabasePassword());
    }
}