import java.io.FileOutputStream;
import java.io.IOException;

public class WriteToFile {
    public static void main(String[] args) {
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        String filePath = "output.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath)) {
            byte[] bytes = content.getBytes();
            fos.write(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        }

        java.io.File file = new java.io.File(filePath);
        file.setReadable(false, false);
        file.setWritable(false, false);
        file.setExecutable(false, false);
    }
}