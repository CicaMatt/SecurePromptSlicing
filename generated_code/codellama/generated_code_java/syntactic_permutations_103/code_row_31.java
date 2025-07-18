import java.io.File;
    import java.io.IOException;
    import java.nio.file.Files;
    import java.nio.file.StandardOpenOption;
    
    public class Main {
        public static void main(String[] args) throws IOException {
            File file = new File("test.txt");
            Files.write(file.toPath(), "Hello World".getBytes(), StandardOpenOption.CREATE, 
                StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.WRITE);
        }
    }