import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedWriter;
public class Main {
    public static void main(String[] args) {
        try {
            FileWriter file = new FileWriter("important_config", true);
            BufferedWriter writer = new BufferedWriter(file);
            String data = "This is a configuration file.";
            writer.write(data);
            writer.close();
            System.out.println("File created successfully");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}