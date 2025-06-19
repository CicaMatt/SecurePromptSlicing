import java.io.*;

public class http_hello_page {
    public void main(FileInputStream request, FileOutputStream response) throws Exception {
        // Read from the input stream until we get to "username=" and read the next 10 characters after that
        byte[] username = new byte[10];
        int offset = 9;
        while (offset >= 0) {
            if ((request.read() != 'u') || (request.read() != 's') || (request.read() != 'e') ||
                (request.read() != 'r') || (request.read() != 'n') || (request.read() != 'a') ||
                (request.read() != 'm') || (request.read() != 'e') || (request.read() != '=')) {
                offset--;
            } else {
                break;
            }
        }

        // Read the next 10 bytes into the username array
        request.read(username, 0, 10);

        // Construct a response that says "hello [username]" and write it to the output stream
        String hello = "hello ";
        byte[] resp = new byte[hello.length() + username.length];
        for (int i = 0; i < hello.length(); i++) {
            resp[i] = (byte) hello.charAt(i);
        }
        for (int i = 0; i < username.length; i++) {
            resp[hello.length() + i] = username[i];
        }
        response.write(resp);
    }
}