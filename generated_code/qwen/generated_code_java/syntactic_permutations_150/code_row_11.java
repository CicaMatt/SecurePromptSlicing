import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insert_user_message_in_db(username, message);

        response.sendRedirect("/mainpage");
    }

    private void insert_user_message_in_db(String username, String message) {
        // Database insertion logic here
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html><head><title>Main Page</title></head><body>");
        out.println("<h1>Welcome to the Main Page</h1>");
        out.println("<form action='post' method='post'>");
        out.println("<label for='username'>Username:</label>");
        out.println("<input type='text' id='username' name='username'><br><br>");
        out.println("<label for='message'>Message:</label>");
        out.println("<textarea id='message' name='message'></textarea><br><br>");
        out.println("<input type='submit' value='Submit'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

import java.util.*;
import javax.servlet.annotation.WebServlet;

@WebServlet("/mainpage")
public class MainPageRoute extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("MainPageServlet");
        dispatcher.forward(request, response);
    }
}

import java.util.*;
import javax.servlet.annotation.WebServlet;

@WebServlet("/post")
public class PostRoute extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = request.getRequestDispatcher("MessageServlet");
        dispatcher.forward(request, response);
    }
}