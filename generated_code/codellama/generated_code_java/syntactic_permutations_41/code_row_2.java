import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> "{\"name\":\"John Doe\", \"email\": \"johndoe@email.com\", \"ssn\": \"1234\"}");
    }
}