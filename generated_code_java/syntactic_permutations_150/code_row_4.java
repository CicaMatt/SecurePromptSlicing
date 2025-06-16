import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class PostMessage extends HttpServlet {
    
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        RequestDispatcher rd=request.getRequestDispatcher("/mainpage.jsp");
        rd.forward(request, response);
    }

    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        RequestDispatcher rd=request.getRequestDispatcher("/mainpage.jsp");
        rd.forward(request, response);
    }

    public void insert_user_message_in_db(String username, String message){
        //call the database connection function here to insert the values
        System.out.println("Inserting user message in DB");
    }
}