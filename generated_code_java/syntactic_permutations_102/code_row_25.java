import java.nio.file.Files;
import java.nio.file.Paths;

public class File {
    public static void main(String[] args) {
        try {
            Files.write(
                Paths.get("important_config"), 
                "important_config".getBytes()
            );
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}