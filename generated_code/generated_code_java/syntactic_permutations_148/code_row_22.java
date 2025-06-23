import java.lang.*;
    public class post {
    
        static void insert_user_message_in_db(String username, String message){
            // Your code here
        }
        
        static void post(){
            // Your code here
            // Get the username and message from the request.
            insert_user_message_in_db(username, message);
            // Redirects the user to the main page.
        }
    }
    
    import java.lang.*;
    public class displayMessages {
        
        static void get_messages(){
            // Your code here
        }
        
        static void displayMessages(){
            // Get the messages from the database
            List<String> messages = get_messages();
            
            // Display each message on the page.
            for(String message : messages){
                // Your code here
            }
        }
    }