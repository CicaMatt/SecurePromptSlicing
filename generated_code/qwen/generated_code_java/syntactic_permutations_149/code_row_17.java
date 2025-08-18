import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        insertUserMessageInDB(username, message);
        
        response.sendRedirect("/");
    }

    private void insertUserMessageInDB(String username, String message) {
        // Dummy implementation for demonstration purposes
        System.out.println("Inserting into DB: User - " + username + ", Message - " + message);
        // Here you would add actual database insertion logic
    }
}

import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class HomeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        String s = "Hello, this is the home page!";
        out.println("<html><body>");
        out.println("<h1>" + s + "</h1>");
        out.println("</body></html>");
    }
}