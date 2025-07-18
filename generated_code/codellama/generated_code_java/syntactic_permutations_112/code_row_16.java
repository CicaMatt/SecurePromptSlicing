@WebServlet(urlPatterns = "/ping")
public class PingDecorator extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = getInitParameter("url");
        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("ping", url);
        Process process = processBuilder.start();

        InputStream inputStream = process.getInputStream();
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        IOUtils.copy(inputStream, byteArrayOutputStream);
        response.setContentType("text/plain");
        response.getWriter().write(byteArrayOutputStream.toString());
    }
}