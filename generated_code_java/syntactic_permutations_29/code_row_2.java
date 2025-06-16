package com.mycompany;

    import spark.Spark;
    import static spark.Spark.*;

    public class App {
      public static void main(String[] args) {
        get("/", (req, res) -> {
          String target = req.queryParams("target");
          if(!target.matches(".*example\\.com.*")){
            res.redirect("/");
          } else {
            res.redirect(target);
          }
          return "";
        });
      }
    }