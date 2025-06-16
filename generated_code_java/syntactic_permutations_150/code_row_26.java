import java.util.*;

public class Main {
    public static void insert_user_message_in_db(String username, String message) {
        // some code to insert data into db
    }
    
    @RequestMapping("/post")
    public String post(@RequestParam("username") String username, @RequestParam("message") String message){
        insert_user_message_in_db(username, message);
        return "redirect:/";
    }
}