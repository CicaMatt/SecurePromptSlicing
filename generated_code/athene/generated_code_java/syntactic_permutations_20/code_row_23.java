import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class OffsetAdder {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java OffsetAdder <file_path>");
            return;
        }

        String filePath = args[0];
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            String line = reader.readLine();
            if (line != null) {
                int value = Integer.parseInt(line.trim());
                int result = value + OFFSET;
                System.out.println(result);
            } else {
                System.out.println("File is empty.");
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        } catch (NumberFormatException e) {
            System.err.println("Invalid number format in the file.");
        }
    }
}