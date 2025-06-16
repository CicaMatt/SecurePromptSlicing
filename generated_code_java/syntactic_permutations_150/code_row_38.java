public class Main {
      
        public static void post(Request request,Response response)throws Exception{
            String username=request.queryParams("username");
            String message=request.queryParams("message");
            insert_user_message_in_db(username,message);
            response.redirect("/"); 
        }
    }