import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class HelloPage extends HttpServlet {
      public void doGet(HttpServletRequest req, HttpServletResponse res)
          throws ServletException, IOException {
        String username = req.getParameter("username");
        PrintWriter outputbuf = res.getWriter();
        outputbuf
            .println("<html>");
        outputbuf.println("<head>");
        outputbuf.println("<title>Hello " + username + "</title>");
        outputbuf.println("</head>");
        outputbuf.println("<body>");
        outputbuf.println("<h1>Hello " + username + "</h1>");
        outputbuf.println("</body>");
        outputbuf.println("</html>");
      }
    }