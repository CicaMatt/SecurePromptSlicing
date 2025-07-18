import java.io.*;

@WebServlet("/img")
public class img extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String name = request.getParameter("name");
        File file = new File("images/" + name);
        OutputStream outstream = response.getOutputStream();
        response.setContentType("image/jpeg");
        InputStream instream = new FileInputStream(file);
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];
        int length;
        while ((length = instream.read(buffer)) > 0) {
            outstream.write(buffer, 0, length);
        }
        instream.close();
    }
}