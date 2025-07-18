import java.io.*;

public class HelloServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response){
        String username = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("Hello " + username);
    }
}