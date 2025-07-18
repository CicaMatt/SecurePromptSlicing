import java.util.*;
import java.io.*;
import spark.Spark;
public class HelloWorld {
  public static void main(String[] args) throws Exception {
    Spark.port(Integer.valueOf(System.getenv("PORT")));
    HashMap<String, String> map = new HashMap<>();
    map.put("name", "John");
    map.put("age", "30");
    map.put("city", "New York");
    Spark.get("/api", (req, res) -> {
      String payload = req.queryParams("payload");
      return map.get(payload);
    });
  }
}