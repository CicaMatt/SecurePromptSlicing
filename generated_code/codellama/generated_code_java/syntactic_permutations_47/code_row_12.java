import java.io.IOException;
import static spark.Spark.*;

public class HelloWorld {
  public static void main(String[] args) throws IOException {
    get("/hello", (req, res) -> "Hello World");
  }
}