import java.io.IOException;
import javax.servlet.http.*;
import java.lang.System;
public class PingService extends HttpServlet {
    private String url = "";

    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        res.getWriter().write("URL " + this.url + " is unavailable");
    }

    public PingService() {
        super();
    }
}