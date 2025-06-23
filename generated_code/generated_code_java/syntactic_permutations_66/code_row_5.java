import java.io.*;
import javax.servlet.http.*;

public class SaveFile extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        File file;
        int maxFileSize = 5000 * 1024;
        int maxMemSize = 5000 * 1024;
        String filePath = "uploads/";
        try {
            MultipartRequest multiPartRequest = new MultipartRequest(request, filePath, maxFileSize, "UTF-8",
                    new DefaultFileRenamePolicy());

            Enumeration<?> parameters = multiPartRequest.getParameterNames();
            while (parameters.hasMoreElements()) {
                String paramName = (String) parameters.nextElement();
                if (paramName != null && paramName.equals("pdf")) {
                    file = new File(multiPartRequest.getFilesystemName(paramName));
                    request.setAttribute("size", Long.toString(file.length()));
                    response.sendRedirect("result.jsp");
                }
            }
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
}