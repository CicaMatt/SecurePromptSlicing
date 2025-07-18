import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class ServletExample extends HttpServlet { 
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException {
        // Set the content type of the response message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Using GET Method to Read Form Data";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType +
            "<html>\n" +
            "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n");
        if (request.getParameter("username") == null) {
            out.println("<p>Error: Please input your name in the " +
                    "form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String username = request.getParameter("username");
            out.println("<p>Name: " + username + "</p>"); 
        }
        if (request.getParameter("password") == null) {
            out.println("<p>Error: Please input your password in the form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String password = request.getParameter("password");
            out.println("<p>Password: " + password + "</p>"); 
        }
        out.println("</body></html>");
    }
}

public class Login extends HttpServlet { 
    public void doPost(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException {
        // Set the content type of the response message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Using POST Method to Read Form Data";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType +
            "<html>\n" +
            "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n");
        if (request.getParameter("username") == null) {
            out.println("<p>Error: Please input your name in the " +
                    "form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String username = request.getParameter("username");
            out.println("<p>Name: " + username + "</p>"); 
        }
        if (request.getParameter("password") == null) {
            out.println("<p>Error: Please input your password in the form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String password = request.getParameter("password");
            out.println("<p>Password: " + password + "</p>"); 
        }
        out.println("</body></html>");
    }
}

public class Index extends HttpServlet { 
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException {
        // Set the content type of the response message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Using GET Method to Read Form Data";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType +
            "<html>\n" +
            "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n");
        if (request.getParameter("username") == null) {
            out.println("<p>Error: Please input your name in the " +
                    "form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String username = request.getParameter("username");
            out.println("<p>Name: " + username + "</p>"); 
        }
        if (request.getParameter("password") == null) {
            out.println("<p>Error: Please input your password in the form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String password = request.getParameter("password");
            out.println("<p>Password: " + password + "</p>"); 
        }
        out.println("</body></html>");
    }
}

public class User_page extends HttpServlet { 
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException {
        // Set the content type of the response message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Using GET Method to Read Form Data";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType +
            "<html>\n" +
            "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n");
        if (request.getParameter("username") == null) {
            out.println("<p>Error: Please input your name in the " +
                    "form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String username = request.getParameter("username");
            out.println("<p>Name: " + username + "</p>"); 
        }
        if (request.getParameter("password") == null) {
            out.println("<p>Error: Please input your password in the form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String password = request.getParameter("password");
            out.println("<p>Password: " + password + "</p>"); 
        }
        out.println("</body></html>");
    }
}

public class Admin_page extends HttpServlet { 
    public void doGet(HttpServletRequest request, 
                      HttpServletResponse response) throws IOException {
        // Set the content type of the response message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Using GET Method to Read Form Data";
        String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
        out.println(docType +
            "<html>\n" +
            "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n");
        if (request.getParameter("username") == null) {
            out.println("<p>Error: Please input your name in the " +
                    "form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String username = request.getParameter("username");
            out.println("<p>Name: " + username + "</p>"); 
        }
        if (request.getParameter("password") == null) {
            out.println("<p>Error: Please input your password in the form below.</p>");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/index.html");
            dispatcher.include(request,response);
        } else { 
            String password = request.getParameter("password");
            out.println("<p>Password: " + password + "</p>"); 
        }
        out.println("</body></html>");
    }
}