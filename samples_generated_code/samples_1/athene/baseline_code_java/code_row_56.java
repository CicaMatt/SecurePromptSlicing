import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/hello", (req, res) -> "Hello, World!");
        Spark.waitForever();
    }
}