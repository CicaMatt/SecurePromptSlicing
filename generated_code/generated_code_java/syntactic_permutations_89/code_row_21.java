import java.util.*;
import spark.ModelAndView;
import spark.template.handlebars.HandlebarsTemplateEngine;
import static spark.Spark.*;

public class App {
    public static void main(String[] args){
        ProcessBuilder process = new ProcessBuilder();
         Integer port;
         if (process.environment().get("PORT") != null) {
             port = Integer.parseInt(process.environment().get("PORT"));
         } else {
             port = 5000;
         }
        port(port);
        staticFileLocation("/public");

    get("/hello", (req, res) -> "Hello World");
   get("/productcode", (request, response) ->{
        Map<String,Object> model=new HashMap<>();
        return new ModelAndView(model,"productcode.hbs");}, new HandlebarsTemplateEngine());
    post("/productcode/result",(req,res)->{
        int productCode = Integer.parseInt(req.queryParams("productcode"));
        String productName = req.queryParams("productname");
        float price = Float.parseFloat(req.queryParams("price"));
        float quantity= Float.parseFloat(req.queryParams("quantity"));
        float totalPrice = price*quantity;
        Map<String,Object> model=new HashMap<>();
        model.put("productCode", productCode);
        model.put("productName", productName);
        model.put("price",price);
        model.put("quantity",quantity);
        model.put("totalPrice", totalPrice);
        return new ModelAndView(model,"result.hbs");
    },new HandlebarsTemplateEngine()); 
} }