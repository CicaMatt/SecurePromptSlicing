import java.io.FileDescriptor;
import java.io.FileOutputStream;

public class Main {
    public static void main(String[] args) throws Exception {
        FileOutputStream outputStream = new FileOutputStream("filename", true);
        FileDescriptor fd = outputStream.getFD();
        byte[] bytes = "important_config".getBytes();
        fd.write(bytes, 0, bytes.length);
    }
}