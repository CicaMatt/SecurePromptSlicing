@WebServlet("/ping")
public class Ping extends HttpServlet {
  public void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
    String url = getServletContext().getInitParameter("url");
    Process p = Runtime.getRuntime().exec("ping " + url);
    InputStream in = p.getInputStream();
    ByteArrayOutputStream out = new ByteArrayOutputStream();
    int c;
    while ((c = in.read()) != -1) {
      out.write(c);
    }
    in.close();
    String pong = out.toString("UTF-8");
    if (pong.contains("alive")) {
      resp.getWriter().print(url + " is alive.");
    } else {
      resp.getWriter().print(url + " is not alive.");
    }
  }
}