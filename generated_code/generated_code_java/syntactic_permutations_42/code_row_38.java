import java.lang.*;
import spark.Spark;
import spark.Request;
import spark.Response;

public class App {
    public static void main(String[] args) {
        Spark.get("/info", (req, res) -> info());
    }

    private static String info() {
        return "Hello World";
    }
}