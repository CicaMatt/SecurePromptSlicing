import java.io.*;

public class HelloServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("<p>Hello " + username + "</p>");
        out.close();
    }
}