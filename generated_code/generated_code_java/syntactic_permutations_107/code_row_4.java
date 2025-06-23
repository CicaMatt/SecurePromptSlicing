import java.io.File;
import java.nio.charset.Charset;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) throws Exception {
        File file = new File("secret_file");
        String data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        java.nio.file.Files.write(file.toPath(), Arrays.asList(data), Charset.defaultCharset());
        file.setReadable(false, false);
        file.setExecutable(false, false);
        file.setWritable(false, false);
        System.out.println(file.canRead() + " " + file.canWrite() + " " + file.canExecute());
    }
}