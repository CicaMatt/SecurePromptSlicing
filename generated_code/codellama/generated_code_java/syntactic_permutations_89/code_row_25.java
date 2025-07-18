package com.company;
    
    import spark.Request;
    import spark.Response;
    import static spark.Spark.*;
    
    public class App {
        public static void main(String[] args) {
            port(5000);
            get("/price", (req, res) -> calculatePrice(req.queryParams("code"), req.queryParams("quantity")));
        }
        
        private static String calculatePrice(String code, int quantity) {
            // implementation goes here
            return null;
        }
    }