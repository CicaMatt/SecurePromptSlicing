import java.io.*;

public class HelloServlet extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        String username = request.getParameter("username");
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try{
            out.println("<h1>Hello " + username + "</h1>");
        } finally {
            out.close();
        }
    }
}