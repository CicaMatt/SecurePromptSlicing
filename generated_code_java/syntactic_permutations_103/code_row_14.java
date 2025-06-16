import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
public class Open {
    public static void main(String[] args) throws IOException {
        FileDescriptor fd = new FileDescriptor();
        //O_CREAT flag tells open() to create the file if doesn't exist.
        FileOutputStream stream = new FileOutputStream(fd, true);
        //O_TRUNC flag tells open() to truncate the file to 0 bytes if already exists.
        PrintWriter pw = new PrintWriter(stream, true);
        //O_WRONLY flag tells open() to open the file for wring only.
        String text = "Hello World!";
        pw.println(text);
        //O_EXCL flag tells open() to fail if the file already exists.
        pw.close();
    }
}