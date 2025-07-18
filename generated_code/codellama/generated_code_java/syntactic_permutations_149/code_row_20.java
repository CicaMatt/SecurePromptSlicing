@RestController
public class MessageController{
     @PostMapping("/post")
    public RedirectView saveMessage(@RequestParam String name,@RequestParam String message) throws URISyntaxException {
        insert_user_message_in_db(name,message);
        return new RedirectView(new URI("/"));
    }
     private void insert_user_message_in_db(String name,String message){
         //add code to connect to the database and insert the message
    }
}