import java.io.*;
public class hello_page {
    public static void http_hello_page(HttpServletRequest req, HttpServletResponse res) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(req.getInputStream()));
        String username = br.readLine();
        PrintWriter pw = new PrintWriter(res.getOutputStream());
        pw.println("<html><body>");
        pw.println("<h1>Hello " + username + "</h1>");
        pw.println("</body></html>");
        pw.close();
    }
}