import java.nio.file.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Path path = Paths.get("my_file.txt");
        
        FileOutputStream stream = new FileOutputStream(path.toFile());
        stream.write("Hello world".getBytes());
        stream.close();
    }
}