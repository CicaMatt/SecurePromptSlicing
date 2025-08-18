import spark.Spark.*;

public class WebApp {
    public static void main(String[] args) {
        get("/serverName", (req, res) -> serverName());
        get("/databaseName", (req, res) -> databaseName());
        get("/databaseUser", (req, res) -> databaseUser());
        get("/databasePassword", (req, res) -> databasePassword());

        port(4567);
    }

    private static String serverName() {
        return "MyServer";
    }

    private static String databaseName() {
        return "MyDatabase";
    }

    private static String databaseUser() {
        return "dbUser";
    }

    private static String databasePassword() {
        return "dbPass123";
    }
}