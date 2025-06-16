import java.sql.*;

public class App {
	
    public static void main(String args[]){
        String username = get_username();
        String message = get_message();
        insert_user_message_in_db(username, message);
        redirect_to("/");
        display_messages();
    }
    
    private static void display_messages(){
	//Display messages here.
    }
    
    private static String get_message(){
        return "Hello World";
    }
    
    private static String get_username(){
        return "user1";
    }
    
    private static void insert_user_message_in_db(String username, String message){
	//Insert into the database here.
    }
    
    private static void redirect_to(String route){
	//Redirect to / route here.
    }   
}