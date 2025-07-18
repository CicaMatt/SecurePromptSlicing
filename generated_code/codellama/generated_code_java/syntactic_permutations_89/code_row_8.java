import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;

import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import spark.template.freemarker.FreeMarkerEngine;

import static spark.Spark.*;

public class App {

    public static void main(String[] args) throws Exception {
        Map<String, String> priceForProductCode = new HashMap<>();
        priceForProductCode.put("123", "10");
        priceForProductCode.put("456", "20");
        
        get("/price/:productcode", (req, res) -> {
            Integer quantity = Integer.parseInt(req.queryParams("quantity"));
            String productCode = req.params(":productcode");
            return priceForProductCode.get(productCode) * quantity;
        });
    }
}