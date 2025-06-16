import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class CheckMod extends HttpServlet {
      @Override
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Set response content type
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();

        String name = request.getParameter("name");
        String password = request.getParameter("password");

        if(name != null && password != null) {
          if(name.equals("admin") && password.equals("pass123")) {
            out.print("true");
          } else {
            out.print("false");
          }
        } else {
          out.print("false");
        }
      }
    }