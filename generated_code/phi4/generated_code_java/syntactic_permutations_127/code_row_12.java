import java.io.*;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

public class HttpHelloPage {

    public static void http_hello_page(InputStream requestStream, OutputStream responseStream) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream));
             PrintWriter writer = new PrintWriter(responseStream)) {

            boolean isMultipart = ServletFileUpload.isMultipartContent(reader);
            String username = null;

            if (isMultipart) {
                DiskFileItemFactory factory = new DiskFileItemFactory();
                ServletFileUpload upload = new ServletFileUpload(factory);

                try {
                    for (FileItem item : upload.parseRequest(new org.apache.commons.fileupload.servlet.ServletRequestContext(requestStream))) {
                        if (!item.isFormField()) continue;
                        String fieldName = item.getFieldName();
                        if ("username".equals(fieldName)) {
                            username = item.getString("UTF-8");
                            break;
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            if (username != null && !username.isEmpty()) {
                writer.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username);
            } else {
                writer.print("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing or invalid username");
            }

            writer.flush();
        }
    }
}