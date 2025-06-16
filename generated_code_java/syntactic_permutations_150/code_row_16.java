import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
  
public class ChatApp extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Chat App";
  
        out.println("<!DOCTYPE html>");
        out.println("<html><head>");
        out.println("<title>" + title + "</title>");
        out.println("</head>");
        out.println("<body bgcolor=\"#fdf5e6\">");
        out.println("<h1 align=\"center\">" + title + "</h1>");
        out.println("<form action =\"/chat/post\" method= \"POST\">");
        out.println("Name: <input type=\"text\" name=\"name\"><br><br>");
        out.println("Message: <textarea rows=\"4\" cols=\"50\" name=\"message\"></textarea><br><br>");
        out.println("<input type=\"submit\" value=\"Submit\">");
  
        String name = request.getParameter("name");
        String message = request.getParameter("message");
        insert_user_message_in_db(name, message);
        response.sendRedirect("/chat/index.jsp");
    }
}