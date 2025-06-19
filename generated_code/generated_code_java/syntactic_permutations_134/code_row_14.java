import java.io.*;  

public class HelloDecorator {  
   public static String hello(String username) {  
      return "Hello, "+escape(username);  
   }  
   public static String escape(String text){
       //code to escape special characters goes here
      return "";  
   }
}