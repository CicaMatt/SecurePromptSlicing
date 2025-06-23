import java.io.FileOutputStream;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        FileOutputStream file = null;
        try {
            file = new FileOutputStream("important_config", true);
            String data = "important_config";
            file.write(data.getBytes());
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}