import java.io.*;

@WebServlet(urlPatterns = {"/ping"})
public class PingServlet extends HttpServlet {
    private String url;

    public void doGet(HttpServletRequest request,
                      HttpServletResponse response) throws IOException {
        String pong = ping();
        PrintWriter out = response.getWriter();
        if (pong.equals("0"))
            out.println("Alive");
        else
            out.println("Not Alive");
    }

    public static String ping() {
        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            int status = process.waitFor();
            return Integer.toString(status);
        } catch (Exception e) {
            return e.getMessage();
        }
    }
}