import java.io.*;

public class MyApp {
    public static void main(String[] args) throws IOException {
        FileOutputStream outputStream = new FileOutputStream("myfile.txt", true);
        String data = "Hello World!";
        byte[] bytes = data.getBytes();
        outputStream.write(bytes);
        outputStream.close();
    }
}