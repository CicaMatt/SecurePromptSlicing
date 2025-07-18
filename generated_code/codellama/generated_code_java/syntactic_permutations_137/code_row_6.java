import java.io.*;
import java.net.*;
public class App {
  public static void main(String[] args) throws Exception {
   // function() called when user visits URL /
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getParameter("session");
     //function() calls auth_mod() with username, password and session 
    boolean auth = auth_mod(username, password, session);
          if (auth) {
      //if user is a moderator
            response.sendRedirect("/moderator-dashboard");
        } else {
             //if user is not a moderator
            response.sendRedirect("/not-authorized");
       }
   } 
    //returns true if the user is a moderator and false if the user is not a moderator
    public boolean auth_mod(String username, String password, String session) {
         //add code to check if user is moderator
        return false;
    }
}