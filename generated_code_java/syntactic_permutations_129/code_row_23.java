import java.util.*;
import java.io.*;
public class MyEnvironment{
   public static void main(String[] args) {
       render_response_from_env();
   }
    private String template;
    private String name;
    
    // Getters and Setters
    public String getTemplate(){
        return this.template;
    }
    public void setTemplate(String template){
        this.template = template;
    }
    public String getName(){
        return this.name;
    }
    public void setName(String name){
        this.name = name;
    }
    
    // Default Constructor
    public MyEnvironment(){
        
    }
    
    // Parametrized Constructor
    public MyEnvironment(String template, String name){
        this.template = template;
        this.name = name;
    }
    
   // render_response_from_env function that takes an environment as an argument
   public void render_response_from_env(){
       //Get the name parameter from the request.
        String nameParameter= "";
        
      /* The function gets the template from the environment.The function renders the template with 
           the name parameter */
       String renderedTemplate = "";
   }
}