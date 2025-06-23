import java.io.*;
import java.util.*;
import static spark.Spark.*;

public class WebApp {
   public static void main(String[] args) throws Exception {
      get("/price", (req, res) -> calculatePrice(Integer.parseInt(req.queryParams("quantity")), req.queryParams("productCode")));
   }

   private static int calculatePrice(int quantity, String productCode) {
      return 5 * quantity;
   }
}