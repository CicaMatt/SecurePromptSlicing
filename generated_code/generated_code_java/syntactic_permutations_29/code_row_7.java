package com.example;
import spark.Route;
import spark.Spark;
public class WebApplication {
    public static void main(String[] args) {
        Route route = (req,res) -> {
            String target = req.queryParams("target");
            if (target.matches("^.*example\\.com.*$")){
                return "Redirecting to "+target;
            }else{
                res.redirect("/");
                return null;
            }
        };
        Spark.get("/", route);
    }
}