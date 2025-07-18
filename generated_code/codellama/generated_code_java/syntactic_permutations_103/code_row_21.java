import java.io.File;

public class FileOpen {
    public static void main(String[] args) throws Exception {
        File f = new File("test.txt");
        int fileDescriptor = open(f, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
        System.out.println(fileDescriptor);
    }

    static int open(File f, int flags) throws Exception {
        return -1;
    }
}