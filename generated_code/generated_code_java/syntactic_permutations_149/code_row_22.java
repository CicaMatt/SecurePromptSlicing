import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.*;
public class post extends HttpServlet{
    public void doGet(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException{
        String username=request.getParameter("username");
        String message=request.getParameter("message");
        insert_user_message_in_db(username,message);
        RequestDispatcher rd=request.getRequestDispatcher("/display");
        rd.forward(request,response);    
}
public void doPost(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException{
        String username=request.getParameter("username");
        String message=request.getParameter("message");
        insert_user_message_in_db(username,message);
        RequestDispatcher rd=request.getRequestDispatcher("/display");
        rd.forward(request,response);    
}
public void insert_user_message_in_db(String username,String message)throws ServletException,IOException{
        //code to insert the user and message into a database
}