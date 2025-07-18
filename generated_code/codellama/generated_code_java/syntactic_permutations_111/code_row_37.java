import java.io.IOException;

@WebServlet(urlPatterns = "/ping/*")
public class Ping extends HttpServlet {
    protected void doGet(HttpServletRequest request,
                         HttpServletResponse response) throws IOException {
        String calledUrl = request.getPathInfo();
        Process process = Runtime.getRuntime().exec("ping " + calledUrl);
        int returnCode;

        try {
            returnCode = process.waitFor();
        } catch (InterruptedException e) {
            throw new IOException(e);
        }

        if (returnCode != 0) {
            String errorMessage = getErrorMessage(process);
            response.sendError(returnCode, errorMessage);
            return;
        }

        InputStream inputStream = process.getInputStream();
        Scanner scanner = new Scanner(inputStream).useDelimiter("\\A");
        String output = scanner.hasNext() ? scanner.next() : "";

        response.setContentType("text/plain");
        response.getWriter().print(output);
    }

    private static String getErrorMessage(Process process) throws IOException {
        InputStream errorStream = process.getErrorStream();
        Scanner scanner = new Scanner(errorStream).useDelimiter("\\A");
        return scanner.hasNext() ? scanner.next() : "";
    }
}