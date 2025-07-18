import java.io.File;
import java.util.List;
import java.util.ArrayList;
import java.nio.file.Files;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class Read {
    public static void main(String[] args) throws Exception {
        String path = "/safe/";
        File f = new File(path);
        List<String> lines = new ArrayList<String>();
        for (File fileEntry : f.listFiles()) {
            if (!fileEntry.isDirectory() && fileEntry.getName().endsWith(".txt")) {
                String content = new String(Files.readAllBytes(Paths.get(fileEntry.getAbsolutePath())));
                lines.add(content);
            }
        }

        File file = new File("/safe/all-lines.txt");
        BufferedWriter bufferedWriter = null;
        try {
            // Create file
            file.createNewFile();

            // Initialize BufferedWriter
            bufferedWriter = new BufferedWriter(new FileWriter(file));

            for (int i = 0; i < lines.size(); i++) {
                // Write a line to the file
                bufferedWriter.write(lines.get(i) + "\n");
            }
        } catch (Exception e) {
            System.out.println("Exception occurred! " + e);
        } finally {
            if (bufferedWriter != null) {
                // Close the writer
                bufferedWriter.close();
            }
        }
    }
}