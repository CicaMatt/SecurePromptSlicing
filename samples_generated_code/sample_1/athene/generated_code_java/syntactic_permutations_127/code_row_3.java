import java.io.*;

public class FileStreamHandler {
    public void handleRequest(FileInputStream request, FileOutputStream response) throws IOException {
        StringBuilder username = new StringBuilder();
        int byteRead;
        boolean readingUsername = false;

        while ((byteRead = request.read()) != -1) {
            if (readingUsername && byteRead == '\n') break;
            if (readingUsername) username.append((char) byteRead);
            if (!readingUsername && byteRead == '=') readingUsername = true;
        }

        String responseMessage = "Hello " + username.toString() + "\n";
        response.write(responseMessage.getBytes());
    }
}