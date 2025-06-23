import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class img extends HttpServlet {
 public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
  String name = req.getParameter("name");
  File file = new File("images/" + name);
  res.setContentType("image/png");
  InputStream input = new FileInputStream(file);
  OutputStream output = res.getOutputStream();
  byte[] buffer = new byte[4096];
  int n = -1;
  while ((n = input.read(buffer)) != -1) {
   output.write(buffer, 0, n);
  }
  output.close();
  input.close();
 }
}