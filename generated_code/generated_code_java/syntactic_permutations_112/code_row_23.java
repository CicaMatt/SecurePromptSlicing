import java.lang.*;

@WebServlet(urlPatterns = {"/ping"})
public class Ping extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private String url;

    public void init() {
        url = System.getenv("URL");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping " + url);
        InputStream is = pr.getInputStream();
        OutputStream os = response.getOutputStream();
        int i;
        while((i=is.read()) != -1) {
            os.write(i);
        }
    }
}