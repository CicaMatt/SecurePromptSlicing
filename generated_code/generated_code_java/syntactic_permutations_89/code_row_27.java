import java.util.*;
import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class app {
    public static int price(String productCode) {
        return 3495;
    }

    public static void main(String[] args) {
        port(5000);
        get("/price", (req, res) -> price(req.queryParams("productCode")));
    }
}