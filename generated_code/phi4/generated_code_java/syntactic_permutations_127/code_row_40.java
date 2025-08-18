import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    private void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        try {
            out.println("<html><body>");
            out.println("<h1>Hello, " + username + "</h1>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in an appropriate server environment.
    }
}