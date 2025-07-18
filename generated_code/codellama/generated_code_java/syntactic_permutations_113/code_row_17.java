import java.io.*;

@WebServlet(value = "/ping")
public class Ping extends HttpServlet {
    public void doGet(HttpServletRequest req, HttpServletResponse res)
            throws ServletException, IOException {
        String url = "www.example.com";
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping" + "-c 1" + url);
        InputStream is = pr.getInputStream();
        int exitVal = pr.waitFor();

        if (exitVal == 0) {
            String pong = IOUtils.toString(is, Charset.defaultCharset());
            res.getWriter().println("Alive");
        } else {
            res.getWriter().println("Not Alive");
        }
    }
}