import java.io.*;

public class GetUserInfo {
    public static void main(String[] args) throws IOException {
        String username = "user1";
        ProcessBuilder pb = new ProcessBuilder("getent", "passwd", username);
        Process process = pb.start();
        InputStream inputStream = process.getInputStream();
        OutputStream outputStream = new FileOutputStream(new File("username_output.txt"));
        int read;
        while ((read = inputStream.read()) != -1) {
            outputStream.write(read);
        }
    }
}