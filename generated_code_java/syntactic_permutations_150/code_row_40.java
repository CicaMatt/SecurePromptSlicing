<pre>
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Post extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username,message);
        response.sendRedirect("/index.html");
    }

    public void insert_user_message_in_db(String username, String message){
        //insert into the database
    }
}
</pre>