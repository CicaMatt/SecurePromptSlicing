import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    @WebServlet("/img")
    public class Img extends HttpServlet {
      private static final long serialVersionUID = 1L;
      private File getFile(String name) throws ServletException, IOException {
        String fileName = "images/" + name;
        return new File(fileName);
      }
      protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        File file = getFile(name);
        response.setContentType(file.toURL().openConnection(), "image/jpeg");
      }
    }