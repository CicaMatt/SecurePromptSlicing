import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/", (req, res) -> "Hello World!");
        Spark.init();
    }
}