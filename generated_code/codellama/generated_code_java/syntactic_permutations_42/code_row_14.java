public class Application extends Route{
      private String username;
      private String email;
      private String ssn;
      
      public Application(){
        get("/info", this::info);
      }
      
      private String info(Request req, Response res){
        return "Username: "+username+"\nEmail: "+email+"\nSSN: "+ssn;
      }
    }