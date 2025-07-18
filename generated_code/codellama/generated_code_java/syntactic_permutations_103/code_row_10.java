import java.io.File;

public class HelloWorld {
    public static void main(String[] args) {
        File f = new File("example.txt");
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
        f.open(flags);
    }
}