import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> "Hello, World!");
        Spark.init();
    }
}