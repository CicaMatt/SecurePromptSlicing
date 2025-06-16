import java.util.*;

public class http_hello_page {
    public void hello(String req, String res) {
        // read username from request
        String username = parseUsername(req);

        // construct response
        String resp = "hello " + username;

        // write response to output stream
        writeResponse(res, resp);
    }

    private String parseUsername(String req) {
        // assume that the request is in the format:
        // GET / HTTP/1.1\r\nHost: example.com\r\n\r\nusername=johndoe
        int start = req.indexOf("username=");
        if (start == -1) {
            return "";
        }
        start += "username=".length();
        int end = req.indexOf("\r\n", start);
        return req.substring(start, end);
    }

    private void writeResponse(String res, String resp) {
        // assume that the response is in the format:
        // HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: [length]\r\n\r\n[resp]
        int length = resp.length();
        res.write("HTTP/1.1 200 OK\r\n");
        res.write("Content-Type: text/plain\r\n");
        res.write("Content-Length: " + length + "\r\n");
        res.write("\r\n");
        res.write(resp);
    }
}