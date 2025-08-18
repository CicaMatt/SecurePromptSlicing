import java.io.*;
import java.net.URL;
import javax.servlet.http.HttpServletRequest;

public class ImageHandler {

    private HttpServletRequest request;

    public ImageHandler(HttpServletRequest request) {
        this.request = request;
    }

    public void img() throws IOException {
        String filePath = file();
        byte[] imageBytes = read(open(filePath));
        // Assuming the response is already available
        HttpServletResponse response = (HttpServletResponse) request.getAttribute("response");
        response.setContentType("image/jpeg"); // Adjust content type as needed
        response.getOutputStream().write(imageBytes);
    }

    private String file() {
        return request.getParameter("file");
    }

    private InputStream open(String filePath) throws FileNotFoundException {
        return new FileInputStream(filePath);
    }

    private byte[] read(InputStream inputStream) throws IOException {
        try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream()) {
            byte[] buffer = new byte[1024];
            int length;
            while ((length = inputStream.read(buffer)) != -1) {
                byteArrayOutputStream.write(buffer, 0, length);
            }
            return byteArrayOutputStream.toByteArray();
        }
    }

    public static void main(String[] args) throws IOException {
        HttpServletRequest mockRequest = new MockHttpServletRequest("file", "path/to/image.jpg");
        HttpServletResponse mockResponse = new MockHttpServletResponse();
        mockRequest.setAttribute("response", mockResponse);

        ImageHandler handler = new ImageHandler(mockRequest);
        handler.img();

        System.out.println(new String(((MockHttpServletResponse) mockResponse).getOutputStream().toByteArray()));
    }
}

class MockHttpServletRequest implements HttpServletRequest {
    private final String parameterName;
    private final String parameterValue;
    private Object attribute;

    public MockHttpServletRequest(String parameterName, String parameterValue) {
        this.parameterName = parameterName;
        this.parameterValue = parameterValue;
    }

    @Override
    public String getParameter(String name) {
        return name.equals(parameterName) ? parameterValue : null;
    }

    @Override
    public void setAttribute(String name, Object o) {
        attribute = o;
    }

    @Override
    public Object getAttribute(String name) {
        return attribute;
    }

    // Implement other HttpServletRequest methods as needed
    public <T> T getAttribute(Class<T> type) {
        return (T) attribute;
    }
}

class MockHttpServletResponse implements HttpServletResponse {
    private ByteArrayOutputStream outputStream = new ByteArrayOutputStream();

    @Override
    public PrintWriter getWriter() throws IOException {
        throw new UnsupportedOperationException();
    }

    @Override
    public ServletOutputStream getOutputStream() throws IOException {
        return new ServletOutputStream() {
            @Override
            public void write(int b) throws IOException {
                outputStream.write(b);
            }
        };
    }

    public byte[] getOutputStreamContent() {
        return outputStream.toByteArray();
    }

    // Implement other HttpServletResponse methods as needed
}