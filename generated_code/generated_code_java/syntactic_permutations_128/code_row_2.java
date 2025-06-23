import java.io.IOException;

public class http_hello_page {
    public static void http_hello_page(String request, String response) throws IOException {
        //read username from the request
        String username = readUsernameFromRequest(request);
        //construct a response that says hello [username]
        String resp = "hello" + username;
        //write the response to the output stream
        writeResponse(response, resp);
    }

    private static void writeResponse(String response, String resp) throws IOException {
        byte[] bytes = resp.getBytes();
        response.write(bytes, 0, bytes.length);
        response.close();
    }

    private static String readUsernameFromRequest(String request) throws IOException {
        return request;
    }
}