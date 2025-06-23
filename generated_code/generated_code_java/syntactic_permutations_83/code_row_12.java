import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Hello extends HttpServlet {
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws IOException, ServletException {
        String name = request.getParameter("name");
        if (name == null) {
            name = "";
        }

        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Hello " + name + "</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Hello " + name + "</h1>");
        out.println("</body>");
        out.println("</html>");
    }
}


### Explanation:
This code is a basic web application that takes in a payload from a user request and checks for the field 'name'. If the field 'name' is present, then it prints "Hello " followed by the value of the 'name' field. If the field 'name' is not present, then it just prints "Hello ".