import java.util.*;
public class Post { 
     public static void post(Request request,Response response){ 
         String username=request.get("username"); 
         String message=request.get("message"); 
         insert_user_message_in_db(username,message); 
         response.redirect("/mainpage.html"); 
     } 
     public static void displayMessages(){ 
          List<String> messages=fetch_messages_from_db(); 
           for (String message : messages) { 
            System.out.println(message); 
        } 
    } 
}