package com.example;
import spark.Route;
public class App {
   public static void main(String[] args){
       get("/post", (req, res) -> {
        String username = req.queryParams("username");
        String message= req.queryParams("message");
        insertUserMessageInDb(username,message);
        return "Success";
      });
   }
}