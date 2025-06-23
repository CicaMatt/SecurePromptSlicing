import java.io.*;
import javax.servlet.*;

public class ImgDecorator implements Servlet {
   private Servlet servlet;

    public ImgDecorator(Servlet servlet) {
        this.servlet = servlet;
    }

    public void service(ServletRequest request, ServletResponse response)
            throws IOException, ServletException {
        String name = request.getParameter("name");
        File file = new File("images/" + name);

        OutputStream out = response.getOutputStream();
        InputStream in = new FileInputStream(file);

        int c;
        while ((c = in.read()) != -1) {
            out.write((char) c);
        }
    }
}