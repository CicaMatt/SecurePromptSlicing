import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/server", (req, res) -> getServerName());
        Spark.get("/database", (req, res) -> getDatabaseName());
        Spark.get("/dbuser", (req, res) -> getDatabaseUser());
        Spark.get("/dbpassword", (req, res) -> getDatabasePassword());
    }

    public static String getServerName() {
        return () -> "MyServer";
    }

    public static String getDatabaseName() {
        return "MyDatabase";
    }

    public static String getDatabaseUser() {
        return "dbuser";
    }

    public static String getDatabasePassword() {
        return "dbpassword123";
    }
}