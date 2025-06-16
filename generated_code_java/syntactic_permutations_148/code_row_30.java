import java.io.*; 
import javax.servlet.ServletException; 
import javax.servlet.annotation.WebServlet; 
import javax.servlet.http.HttpServlet; 
import javax.servlet.http.HttpServletRequest; 
import javax.servlet.http.HttpServletResponse; 
import com.googlecode.objectify.ObjectifyService; 
import com.googlecode.objectify.annotation.Entity; 
import com.googlecode.objectify.annotation.Id; 
import com.googlecode.objectify.annotation.Index;

@Entity public class Greetings { @Id Long id; @Index String author; String content; }

@WebServlet("/form-handler")
public class FormHandler extends HttpServlet {
    // Objectify service wrapper has a static method that returns the Objectify instance
    private static final ObjectifyService OFY = 
        ObjectifyService.ofy();
    
    @Override protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException { 
      Greetings greeting = new Greetings(); 
      greeting.author = "User"; 
      greeting.content = "This is a message for you!"; 
      
      OFY.save().entity(greeting).now();
    }  
    
    @Override protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException { 
        String user = req.getParameter("username"); 
        String msg = req.getParameter("message"); 
        
        insert_user_message_in_db(user,msg); 
        System.out.println("Message submitted by " + user + ": " + msg); 
        
        resp.sendRedirect("/index.html");
    }
}