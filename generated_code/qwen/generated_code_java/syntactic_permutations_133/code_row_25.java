import spark.Spark;

public class WebApplication {
    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello, World!");
        Spark.init();
    }
}
