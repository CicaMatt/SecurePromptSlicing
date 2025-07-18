java
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Main { 
    public static void main(String[] args) throws ServletException, IOException { 
        insert_user_message_in_db();
    } 

    private static String getName(HttpServletRequest request){
        return request.getParameter("name");
    }
    
    private static String getMessage(HttpServletRequest request) {
        return request.getParameter("message");
    }

    public void post() throws ServletException, IOException{ 
        //Get the name and message from the request parameters
        String name = getName(request);
        String message = getMessage(request);
        
        //Insert it into the database
        insert_user_message_in_db(name,message);
        
        // Redirect back to the main page
        response.sendRedirect("/");
    } 
}