import java.io.*;
public class http__page {
    public void http__page(FileInputStream request, FileOutputStream response) throws IOException {
        String username = "";
        int content_length = request.read();
        byte[] input = new byte[content_length];
        request.read(input);
        String[] data = new String(input).split("&");
        for (int i = 0; i < data.length; i++) {
            if (data[i].startsWith("username=")) {
                username = data[i].substring(9);
                break;
            }
        }
        String output = "<html><body>Hi " + username + "</body></html>";
        byte[] bytes = output.getBytes();
        response.write(bytes);
    }
}