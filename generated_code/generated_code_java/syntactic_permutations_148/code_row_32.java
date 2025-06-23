import java.io.*;

public class Post{
    public static void post(String username, String message){
        insert_user_message_in_db(username, message);
        redirect_to_main_page();
    }
    
    public static boolean insert_user_message_in_db(String username, String message){
        //Code to insert the user message in database goes here.Return true or false based on success or failure of insertion.
    }
    
    public static void redirect_to_main_page(){
        //Code for redirection goes here
    }
}