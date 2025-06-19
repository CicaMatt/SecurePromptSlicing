package io.marauder.decorators;
import io.marauder.templates;
public class HelloDecorator {
   private String function_name = "/hello/<username>";
   public void bind(String username) {
       templates.render("hello.html", username);
   } 
}