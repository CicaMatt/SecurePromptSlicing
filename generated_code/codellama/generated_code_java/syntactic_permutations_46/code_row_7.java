import java.io.*; 
@WebServlet(urlPatterns = "/img")
public class ImageServlet extends HttpServlet {
  protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    String name = req.getParameter("name");
    File file = new File("images/" + name);
    OutputStream os = resp.getOutputStream();
    InputStream is = new FileInputStream(file);
    byte[] buffer = new byte[1024];
    int read;
    while ((read = is.read(buffer)) != -1) {
      os.write(buffer, 0, read);
    }
  }
}